//
// Created by luxsolari on 09/01/2024.
//
#ifdef WINDOWS_PLATFORM
#include <iostream>
#include <vector>
#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#include "WindowsConsole.h"

const WindowsConsole* WindowsConsole::getInstance() {
    static const WindowsConsole instance;
    return &instance;
}

const WindowsConsole* WindowsConsole::printAddress() const {
    return this;
}

void WindowsConsole::printClassName() {
    std::cout << "WindowsConsole" << std::endl;
}

std::vector<int> WindowsConsole::getConsoleSize() const {
    // return size of console window
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return {csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom - csbi.srWindow.Top + 1};
}

// Draws a square border with the specified width and height. The border is drawn from startPos.
// startPos is a vector with two elements: the x and y coordinates of the start position.
// The border is drawn using unicode characters. The console is set to UTF-16 mode to print unicode characters.
// The console is returned to ANSI mode after the border is drawn.
void WindowsConsole::drawSquareBorder(int width, int height, std::vector<int> startPos) const {
    // ASCII Symbols for borders
    const std::wstring TOP_LEFT_CORNER   = L"\u250C";
    const std::wstring TOP_RIGHT_CORNER  = L"\u2510";
    const std::wstring BOTTOM_LEFT_CORNER= L"\u2514";
    const std::wstring BOTTOM_RIGHT_CORNER= L"\u2518";
    const std::wstring HORIZONTAL_BORDER = L"\u2500";
    const std::wstring VERTICAL_BORDER   = L"\u2502";

    // Set console to UTF-16 mode to print unicode characters to console window (Windows only)
    _setmode(_fileno(stdout), _O_U16TEXT);

    // Set cursor position to start position
    setCursorPosition(startPos.at(0), startPos.at(1));

    // Draw top border
    std::wcout << TOP_LEFT_CORNER;
    for (int i = 0; i < width - 2; ++i) {
        std::wcout << HORIZONTAL_BORDER;
    }
    std::wcout << TOP_RIGHT_CORNER;

    // Draw sides
    for (int i = 0; i < height - 2; ++i) {
        setCursorPosition(startPos.at(0), startPos.at(1) + i + 1);
        std::wcout << VERTICAL_BORDER;
        setCursorPosition(startPos.at(0) + width - 1, startPos.at(1) + i + 1);
        std::wcout << VERTICAL_BORDER;
    }

    // Draw bottom border
    setCursorPosition(startPos.at(0), startPos.at(1) + height - 1);
    std::wcout << BOTTOM_LEFT_CORNER;
    for (int i = 0; i < width - 2; ++i) {
        std::wcout << HORIZONTAL_BORDER;
    }
    std::wcout << BOTTOM_RIGHT_CORNER;
    std::wcout << std::endl;

    // Return console to ANSI mode
    _setmode(_fileno(stdout), _O_TEXT);
}


void WindowsConsole::setConsoleSize(int width, int height) const {
    // Set console window size
    SMALL_RECT windowSize = {0, 0, static_cast<SHORT>(width), static_cast<SHORT>(height)};
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);

    // Set console buffer size
    COORD bufferSize = {static_cast<SHORT>(width), static_cast<SHORT>(height)};
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);

    // Set console window position
    SetWindowPos(GetConsoleWindow(), nullptr, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

    // Set console window title
    SetConsoleTitle("Cards");

}

void WindowsConsole::setCursorPosition(int x, int y) const {
    // Set cursor position
    COORD coord = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void WindowsConsole::moveCursorUp(int steps) const {
    // Get current cursor position
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    // Set cursor position
    COORD coord = {csbi.dwCursorPosition.X, static_cast<SHORT>(csbi.dwCursorPosition.Y - steps)};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void WindowsConsole::moveCursorDown(int steps) const {
    // Get current cursor position
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    // Set cursor position
    COORD coord = {csbi.dwCursorPosition.X, static_cast<SHORT>(csbi.dwCursorPosition.Y + steps)};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void WindowsConsole::moveCursorLeft(int steps) const {
    // Get current cursor position
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    // Set cursor position
    COORD coord = {static_cast<SHORT>(csbi.dwCursorPosition.X - steps), csbi.dwCursorPosition.Y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void WindowsConsole::moveCursorRight(int steps) const {
    // Get current cursor position
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    // Set cursor position
    COORD coord = {static_cast<SHORT>(csbi.dwCursorPosition.X + steps), csbi.dwCursorPosition.Y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void WindowsConsole::returnCursorToStart() const {
    // Set cursor position
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void WindowsConsole::clearScreen() const {
    // Get console window size
    std::vector<int> consoleSize = getConsoleSize();
    int width = consoleSize.at(0);
    int height = consoleSize.at(1);
    // Clear screen
    for (int i = 0; i < height; ++i) {
        setCursorPosition(0, i);
        for (int j = 0; j < width; ++j) {
            std::cout << " ";
        }
    }
    // Return cursor to start
    returnCursorToStart();
}

void WindowsConsole::returnCarriage() const {
    // Get current cursor position
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    // Set cursor position
    COORD coord = {0, csbi.dwCursorPosition.Y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

std::vector<int> WindowsConsole::getCursorPosition() const {
    // Get current cursor position
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return {csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y};
}


#endif //WINDOWS_PLATFORM
