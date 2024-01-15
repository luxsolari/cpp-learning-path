/*

#ifdef UNIX_PLATFORM
#include <ncurses.h>
#endif

#include <iostream>
#include <thread>
#include "Utils/ConsoleFactory.h"

int main() {

#ifdef UNIX_PLATFORM
    // get terminal type
    char *termType = getenv("TERM");
    std::cout << "Terminal type: " << termType << std::endl;
    // set locale
    setlocale(LC_ALL, "C/UTF-8/C/C/C/C");

    initscr();  // Initialize curses mode
    start_color();  // Enable color support if needed
    raw();  // Disable line buffering
    keypad(stdscr, TRUE);  // Enable special keys
    noecho();  // Don't display pressed keys

    // draw border around screen
    box(stdscr, 0, 0);

    // set invisible cursor
    curs_set(0);

    // get screen size
    int x{0};
    int y{0};
    getmaxyx(stdscr, y, x);
    std::string message = "Hello, world!";

    // print on center of screen
    mvprintw(y / 2, (x / 2) - (message.length() / 2), "Hello, world!");
    mvprintw(y / 2, (x / 2) - (message.length() / 2), "  ♠︎ ♣︎ ♥︎ ♦︎  ");

    // refresh screen
    refresh();
    // wait for enter key
    std::wcin.get();

    // end ncurses
    endwin();
#endif

    Console* console = ConsoleFactory::createConsole();

    console->drawSquareBorder(console->getWidth(), console->getHeight() - 1, {0, 0});
    std::string message = "Console Test";
    console->printToConsoleAtLocation(console->getHeight() / 2,
                                      (console->getWidth() / 2) - (int)message.length() / 2,
                                      message.c_str());

    std::cin.get();
    return 0;
}
*/

#include <iostream>
#include <unordered_map>
#include <Windows.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>

class InputManager {
public:
    InputManager();
    ~InputManager();
    void Start();
    void Stop();
    void InputThreadFunction();
    void Update();
    bool IsKeyDown(int key);
    bool IsKeyPressed(int key);
    bool IsKeyReleased(int key);

private:
    std::unordered_map<int, bool> keyStates;
    std::unordered_map<int, bool> prevKeyStates;
    bool running;
    std::thread inputThread;
    mutable std::mutex inputMutex;

    void LockInput() const {
        inputMutex.lock();
    }

    void UnlockInput() const {
        inputMutex.unlock();
    }
};

InputManager::InputManager() : running(true) {
}

InputManager::~InputManager() {
    Stop();  // Ensure the input thread is stopped before exiting
}

void InputManager::Start() {
    inputThread = std::thread(&InputManager::InputThreadFunction, this);
}

void InputManager::Stop() {
    running = false;
    if (inputThread.joinable()) {
        inputThread.join();
    }
}

void InputManager::InputThreadFunction() {
    while (running) {
        Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));  // Adjust as needed
    }
}

void InputManager::Update() {
    LockInput();  // Lock the mutex before accessing shared data

    prevKeyStates = keyStates;

    for (int key = 0; key < 256; ++key) {
        keyStates[key] = GetAsyncKeyState(key) & 0x8000;
    }

    UnlockInput();  // Unlock the mutex after updating shared data
}

bool InputManager::IsKeyDown(int key) {
    LockInput();
    bool result = keyStates.find(key) != keyStates.end() && keyStates.at(key);
    UnlockInput();
    return result;
}

bool InputManager::IsKeyPressed(int key) {
    LockInput();
    bool result = keyStates.find(key) != keyStates.end() && !prevKeyStates[key] && keyStates[key];
    UnlockInput();
    return result;
}

bool InputManager::IsKeyReleased(int key) {
    LockInput();
    bool result = keyStates.find(key) != keyStates.end() && prevKeyStates[key] && !keyStates[key];
    UnlockInput();
    return result;
}

enum class MenuOrientation {
    Vertical,
    Horizontal
};

class ConsoleMenu {
public:
    ConsoleMenu(const std::vector<std::string>& options, MenuOrientation orientation);
    void Run();

private:
    std::vector<std::string> menuOptions;
    size_t selectedOption;
    MenuOrientation orientation;

    void DisplayMenu() const;
};

ConsoleMenu::ConsoleMenu(const std::vector<std::string>& options, MenuOrientation orientation)
        : menuOptions(options), selectedOption(0), orientation(orientation) {
}

void SetConsoleTextAttribute(WORD attributes) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attributes);
}

void ConsoleMenu::DisplayMenu() const {
    system("cls");  // Clear the console (Windows-specific, use "clear" for Unix)

    std::cout << "Select an option:\n";

    for (size_t i = 0; i < menuOptions.size(); ++i) {
        if (i == selectedOption) {
            SetConsoleTextAttribute(FOREGROUND_INTENSITY | FOREGROUND_RED |
                                              BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN);  // Highlighted text color
        }

        std::cout << menuOptions[i];

        if (orientation == MenuOrientation::Vertical) {
            std::cout << "\n";
        } else if (i < menuOptions.size() - 1) {
            std::cout << "   ";  // Space between horizontal options
        }

        if (i == selectedOption) {
            SetConsoleTextAttribute(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  // Reset text color
        }
    }
}

void ConsoleMenu::Run() {
    InputManager inputManager;

    inputManager.Start();

    while (true) {
        DisplayMenu();

        if (orientation == MenuOrientation::Vertical) {
            if (inputManager.IsKeyPressed(VK_DOWN) && selectedOption < menuOptions.size() - 1) {
                ++selectedOption;
            }

            if (inputManager.IsKeyPressed(VK_UP) && selectedOption > 0) {
                --selectedOption;
            }
        } else {
            if (inputManager.IsKeyPressed(VK_RIGHT) && selectedOption < menuOptions.size() - 1) {
                ++selectedOption;
            }

            if (inputManager.IsKeyPressed(VK_LEFT) && selectedOption > 0) {
                --selectedOption;
            }
        }

        if (inputManager.IsKeyPressed(VK_RETURN)) {
            // Process the selected option
            std::cout << "You selected: " << menuOptions[selectedOption] << "\n";
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));  // Adjust as needed
    }

    inputManager.Stop();  // Stop the input thread before exiting
}

int main() {
    std::vector<std::string> options = {"Option 1", "Option 2", "Option 3"};

    ConsoleMenu verticalMenu(options, MenuOrientation::Vertical);
    ConsoleMenu horizontalMenu(options, MenuOrientation::Horizontal);

    std::cout << "Vertical Menu:\n";
    verticalMenu.Run();

    std::cout << "\nHorizontal Menu:\n";
    horizontalMenu.Run();

    return 0;
}
