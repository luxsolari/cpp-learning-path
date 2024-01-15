//
// Created by luxsolari on 09/01/2024.
//
#ifdef WINDOWS_PLATFORM
#include <iostream>
#include <vector>
#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#include <conio.h>
#include <thread>
#include <chrono>
#include "WindowsConsole.h"

WindowsConsole* WindowsConsole::getInstance() {
    static WindowsConsole instance;
    // initialize variables here
    instance.m_isActive = true;

    std::vector<int> consoleSize = instance.getConsoleSize();
    instance.m_width = consoleSize.at(0);
    instance.m_height = consoleSize.at(1);
    instance.m_cursorX = 0;
    instance.m_cursorY = 0;

    // hide cursor
    //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //CONSOLE_CURSOR_INFO cursorInfo;
    //GetConsoleCursorInfo(hConsole, &cursorInfo);
    //cursorInfo.bVisible = false;
    //SetConsoleCursorInfo(hConsole, &cursorInfo);

    return &instance;
}

const WindowsConsole* WindowsConsole::getAddress() const {
    return this;
}

void WindowsConsole::printClassName() const {
    std::cout << "WindowsConsole" << std::endl;
}

std::vector<int> WindowsConsole::getConsoleSize() const {
    // Get console window size
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    return std::vector<int>{width, height};
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
    this->printToConsoleWide(TOP_LEFT_CORNER.c_str());
    for (int i = 0; i < width - 2; ++i) {
       this->printToConsoleWide(HORIZONTAL_BORDER.c_str());
    }
    this->printToConsoleWide(TOP_RIGHT_CORNER.c_str());

    // Draw sides
    for (int i = 0; i < height - 2; ++i) {
        setCursorPosition(startPos.at(0), startPos.at(1) + i + 1);
        this->printToConsoleWide(VERTICAL_BORDER.c_str());
        setCursorPosition(startPos.at(0) + width - 1, startPos.at(1) + i + 1);
        this->printToConsoleWide(VERTICAL_BORDER.c_str());
    }

    // Draw bottom border
    setCursorPosition(startPos.at(0), startPos.at(1) + height - 1);
    this->printToConsoleWide(BOTTOM_LEFT_CORNER.c_str());
    for (int i = 0; i < width - 2; ++i) {
        this->printToConsoleWide(HORIZONTAL_BORDER.c_str());
    }
    this->printToConsoleWide(BOTTOM_RIGHT_CORNER.c_str());
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
    return std::vector<int>{csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y};
}

void WindowsConsole::printToConsole(const char *format, ...) const {
    // print to console window (Windows only)
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

void WindowsConsole::printToConsoleWide(const wchar_t *format, ...) const {
    // print with wide chars to console window (Windows only)
    _setmode(_fileno(stdout), _O_U16TEXT);
    va_list args;
            va_start(args, format);
    vwprintf((wchar_t*)format, args);
            va_end(args);
    // return console to ANSI mode
    _setmode(_fileno(stdout), _O_TEXT);
}

void WindowsConsole::printToConsoleAtLocation(int y, int x, const char *format, ...) const {
    // Set cursor position
    setCursorPosition(x, y);
    // print to console window (Windows only)
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

#endif //WINDOWS_PLATFORM
