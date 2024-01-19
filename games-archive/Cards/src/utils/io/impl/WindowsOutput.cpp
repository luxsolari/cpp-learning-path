//
// Created by luxsolari on 09/01/2024.
//
#ifdef WINDOWS_PLATFORM
#include <iostream>
#include <vector>
#include <Windows.h>
#include <fcntl.h>
#include <io.h>
#include <thread>
#include <chrono>
#include <curses.h>
#include "WindowsOutput.h"

WindowsOutput* WindowsOutput::getInstance() {
    static WindowsOutput instance;
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

    // initialize curses
    setlocale(LC_ALL, "");
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    start_color();
    curs_set(FALSE);

    // initialize colors
    init_pair(1, COLOR_HIGHLIGHTTEXT, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);

    return &instance;
}

const WindowsOutput* WindowsOutput::getAddress() const {
    return this;
}

void WindowsOutput::printClassName() const {
    std::cout << "WindowsOutput" << std::endl;
}

std::vector<int> WindowsOutput::getConsoleSize() const {
    // Get console window size
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    return std::vector<int>{width, height};
}

// Draws a square border with the specified width and height using curses
void WindowsOutput::drawSquareBorder(int width, int height, std::vector<int> startPos) const {
    WINDOW *win = newwin(height, width, startPos.at(0), startPos.at(1));
    ::box(win, 0, 0);
    ::refresh();
    ::wrefresh(win);
}


void WindowsOutput::setConsoleSize(int width, int height) const {
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

void WindowsOutput::setCursorPosition(int x, int y) const {
    // Set cursor position
    COORD coord = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void WindowsOutput::moveCursorUp(int steps) const {
    // Get current cursor position
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    // Set cursor position
    COORD coord = {csbi.dwCursorPosition.X, static_cast<SHORT>(csbi.dwCursorPosition.Y - steps)};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void WindowsOutput::moveCursorDown(int steps) const {
    // Get current cursor position
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    // Set cursor position
    COORD coord = {csbi.dwCursorPosition.X, static_cast<SHORT>(csbi.dwCursorPosition.Y + steps)};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void WindowsOutput::moveCursorLeft(int steps) const {
    // Get current cursor position
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    // Set cursor position
    COORD coord = {static_cast<SHORT>(csbi.dwCursorPosition.X - steps), csbi.dwCursorPosition.Y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void WindowsOutput::moveCursorRight(int steps) const {
    // Get current cursor position
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    // Set cursor position
    COORD coord = {static_cast<SHORT>(csbi.dwCursorPosition.X + steps), csbi.dwCursorPosition.Y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void WindowsOutput::returnCursorToStart() const {
    // Set cursor position
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void WindowsOutput::clearScreen() const {
    // Clear screen
    ::clear();
    ::refresh();
}

void WindowsOutput::returnCarriage() const {
    // Get current cursor position
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    // Set cursor position
    COORD coord = {0, csbi.dwCursorPosition.Y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

std::vector<int> WindowsOutput::getCursorPosition() const {
    // Get current cursor position
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return std::vector<int>{csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y};
}

void WindowsOutput::printToConsole(const char *format, ...) const {
    // print to console window with curses
    va_list args;
    va_start(args, format);
    ::printw(format, args); // Use :: to refer to the global namespace
    ::refresh();
    va_end(args);
}

void WindowsOutput::printToConsoleWide(const wchar_t *format, ...) const {
    // print with wide chars to console window (Windows only)
    _setmode(_fileno(stdout), _O_U16TEXT);
    va_list args;
            va_start(args, format);
    vwprintf((wchar_t*)format, args);
            va_end(args);
    // return console to ANSI mode
    _setmode(_fileno(stdout), _O_TEXT);
}

void WindowsOutput::printToConsoleAtLocation(int y, int x, const char *format, ...) const {
    // print to console window
    va_list args;
    va_start(args, format);
    ::mvprintw(y, x, format, args); // Use :: to refer to the global namespace
    ::refresh();
    va_end(args);
}

WindowsOutput::~WindowsOutput() {
    // return console to ANSI mode
    _setmode(_fileno(stdout), _O_TEXT);
    // return console to normal state
    endwin();
}

#endif //WINDOWS_PLATFORM
