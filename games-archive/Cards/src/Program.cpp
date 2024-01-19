#ifdef UNIX_PLATFORM
#include <ncurses.h>
#include <ios>
#endif
#include <iostream>
#include <thread>
#include "utils/factory/OutputFactory.h"

#ifdef UNIX_PLATFORM
int main() {
    setlocale(LC_ALL, "");
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    start_color();
    curs_set(FALSE);
    set_escdelay(0);

    int height, width, start_y, start_x;
    height = 6;
    width = 8;
    start_y = start_x = 10;

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);

    WINDOW* CARD1 = newwin(height, width, start_y, start_x);
    WINDOW* CARD2 = newwin(height, width, start_y, start_x * 2);
    WINDOW* CARD3 = newwin(height, width, start_y, start_x * 3);
    WINDOW* CARD4 = newwin(height, width, start_y, start_x * 4);
    WINDOW* CARD5 = newwin(height, width, start_y, start_x * 5);

    refresh();
    box(CARD1, 0, 0);
    box(CARD2, 0, 0);
    box(CARD3, 0, 0);
    box(CARD4, 0, 0);
    box(CARD5, 0, 0);

    static const char *card_suits[4] = {"\u2666", "\u2660", "\u2665", "\u2663"};

    mvwprintw(CARD1, 1, 3, "%s", card_suits[1]);
    mvwprintw(CARD1, 1, 1, "10");
    wrefresh(CARD1);

    mvwprintw(CARD2, 1, 3, "%s", card_suits[2]);
    mvwprintw(CARD2, 1, 1, "J");
    wrefresh(CARD2);

    mvwprintw(CARD3, 1, 3, "%s", card_suits[3]);
    mvwprintw(CARD3, 1, 1, "Q");
    wrefresh(CARD3);

    mvwprintw(CARD4, 1, 3, "%s", card_suits[0]);
    mvwprintw(CARD4, 1, 1, "K");
    wrefresh(CARD4);

    mvwprintw(CARD5, 1, 3, "%s", card_suits[1]);
    mvwprintw(CARD5, 1, 1, "A");
    wrefresh(CARD5);

    getch();
    endwin();

    std::cout << "Finalizing program! Press [ENTER] key to exit." << std::endl;
    std::cin.get();

    return 0;
}
#endif


#ifdef WINDOWS_PLATFORM

#include <Windows.h>
#include <chrono>
#include <vector>
#include "utils/io/Input.h"
#include "utils/factory/InputFactory.h"
#include <curses.h>

#pragma execution_character_set( "utf-8" )

enum class MenuOrientation {
    Vertical,
    Horizontal
};

class ConsoleMenu {
public:
    ConsoleMenu(const std::vector<std::string>& options, MenuOrientation orientation, Input* inputManager, Output* console);
    void Run();

private:
    Input* inputManager;
    Output* console;
    std::vector<std::string> menuOptions;
    size_t selectedOption;
    MenuOrientation orientation;

    void DisplayMenu() const;
};

ConsoleMenu::ConsoleMenu(const std::vector<std::string>& options, MenuOrientation orientation, Input* inputManager, Output* console)
        : menuOptions(options), selectedOption(0), orientation(orientation), inputManager(inputManager), console(console) {
}

void SetConsoleTextAttribute(WORD attributes) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attributes);
}

void ConsoleMenu::DisplayMenu() const {
    std::cout << "Select an option:\n";

    for (size_t i = 0; i < menuOptions.size(); ++i) {
        // Set the text color to red if the option is selected
        if (i == selectedOption) {
            // hihglight selected option with red color using ncurses
            attron(COLOR_PAIR(1));
        }

        console->printToConsoleAtLocation(static_cast<int>(i) + 1, 1, menuOptions[i].c_str());

        if (i == selectedOption) {
            // turn off highlight
            attroff(COLOR_PAIR(1));
        }

        if (orientation == MenuOrientation::Vertical) {
            std::cout << "\n";
        } else if (i < menuOptions.size() - 1) {
            std::cout << "   ";  // Space between horizontal options
        }

    }
}

void ConsoleMenu::Run() {
    int maxConsoleX = console->getConsoleSize().at(0);
    int maxConsoleY = console->getConsoleSize().at(1);

    while (true) {
        console->clearScreen();
        console->drawSquareBorder(maxConsoleX, maxConsoleY - 1, {0, 0});
        DisplayMenu();
        if (orientation == MenuOrientation::Vertical) {
            if (inputManager->IsKeyPressed(VK_DOWN) && selectedOption < menuOptions.size() - 1) {
                ++selectedOption;
            }

            if (inputManager->IsKeyPressed(VK_UP) && selectedOption > 0) {
                --selectedOption;
            }
        } else {
            if (inputManager->IsKeyPressed(VK_RIGHT) && selectedOption < menuOptions.size() - 1) {
                ++selectedOption;
            }

            if (inputManager->IsKeyPressed(VK_LEFT) && selectedOption > 0) {
                --selectedOption;
            }
        }

        if (inputManager->IsKeyPressed(VK_RETURN)) {
            // Process the selected option
            if (orientation == MenuOrientation::Vertical) {
                console->moveCursorDown(2);
            } else {
                console->moveCursorDown(2);
                console->returnCarriage();
            }
            std::cout << "You selected: " << menuOptions[selectedOption] << "\n";
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));  // Adjust as needed
    }
}

int main() {
    SetConsoleOutputCP( 65001 );
    Input* inputManager = InputFactory::createInput();
    Output* console = OutputFactory::createConsole();

    std::string greeting = "UI Menu Test! \u2660 \u2663 \u2665 \u2666";

    int maxConsoleX = console->getConsoleSize().at(0);
    int maxConsoleY = console->getConsoleSize().at(1);

    console->drawSquareBorder(maxConsoleX, maxConsoleY - 1, {0, 0});
    console->printToConsoleAtLocation( maxConsoleY / 2,
                                       (maxConsoleX / 2) - static_cast<int>(greeting.length() / 2),
                                       greeting.c_str());

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));  // Adjust as needed

    inputManager->Start();
    std::vector<std::string> options = {"Spade \u2660", "Club \u2663", "Heart \u2665", "Diamond \u2666"};

    ConsoleMenu verticalMenu(options, MenuOrientation::Horizontal, inputManager, console);
    std::cout << "Horizontal Menu:\n";
    verticalMenu.Run();

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));  // Adjust as needed

    ConsoleMenu horizontalMenu(options, MenuOrientation::Vertical, inputManager, console);
    std::cout << "\nVertical Menu:\n";

    horizontalMenu.Run();

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));  // Adjust as needed
    inputManager->Stop();

    return 0;
}
#endif
