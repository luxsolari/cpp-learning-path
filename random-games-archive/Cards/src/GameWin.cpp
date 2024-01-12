//
// Created by luxsolari on 09/01/2024.
//
#ifdef WINDOWS_PLATFORM
#include <iostream>
#include <vector>
#include <Windows.h>
#include "GameWin.h"

GameWin::GameWin() = default;

GameWin::~GameWin() = default;

const GameWin* GameWin::getInstance() {
    static const GameWin instance;
    return &instance;
}

const GameWin* GameWin::printAddress() const {
    return this;
}

void GameWin::printClassName() {
    std::cout << "GameWin" << std::endl;
}

std::vector<int> GameWin::getConsoleSize() const {
    // return size of console window
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return {csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom - csbi.srWindow.Top + 1};
}

void GameWin::drawBorder(int width, int height) const {
    // Draw top border
    for (int i = 0; i < width; ++i) {
        std::cout << "-";
    }
    std::cout << std::endl;

    // Draw sides
    for (int i = 0; i < height - 2; ++i) {
        std::cout << "*";
        for (int j = 0; j < width - 2; ++j) {
            std::cout << " ";
        }
        std::cout << "*" << std::endl;
    }

    // Draw bottom border
    for (int i = 0; i < width; ++i) {
        std::cout << "-";
    }
    std::cout << std::endl;
}

void GameWin::setConsoleSize(int width, int height) const {
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

void GameWin::setCursorPosition(int x, int y) const {
    // Set cursor position
    COORD coord = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GameWin::moveCursorUp(int steps) const {
    // Get current cursor position
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    // Set cursor position
    COORD coord = {csbi.dwCursorPosition.X, static_cast<SHORT>(csbi.dwCursorPosition.Y - steps)};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GameWin::moveCursorDown(int steps) const {
    // Get current cursor position
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    // Set cursor position
    COORD coord = {csbi.dwCursorPosition.X, static_cast<SHORT>(csbi.dwCursorPosition.Y + steps)};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GameWin::moveCursorLeft(int steps) const {
    // Get current cursor position
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    // Set cursor position
    COORD coord = {static_cast<SHORT>(csbi.dwCursorPosition.X - steps), csbi.dwCursorPosition.Y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GameWin::moveCursorRight(int steps) const {
    // Get current cursor position
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    // Set cursor position
    COORD coord = {static_cast<SHORT>(csbi.dwCursorPosition.X + steps), csbi.dwCursorPosition.Y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GameWin::returnCursorToStart() const {
    // Set cursor position
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GameWin::clearScreen() const {
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

void GameWin::returnCarriage() const {
    // Get current cursor position
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    // Set cursor position
    COORD coord = {0, csbi.dwCursorPosition.Y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GameWin::drawCard(int x, int y, int width, int height) const {
    // Draw top border
    setCursorPosition(x, y);
    for (int i = 0; i < width; ++i) {
        std::cout << "-";
    }

    // Draw sides
    for (int i = 0; i < height - 2; ++i) {
        setCursorPosition(x, y + i + 1);
        std::cout << "|";
        setCursorPosition(x + width - 1, y + i + 1);
        std::cout << "|";
    }

    // Draw bottom border
    setCursorPosition(x, y + height - 1);
    for (int i = 0; i < width; ++i) {
        std::cout << "-";
    }
}

std::vector<int> GameWin::getCursorPosition() const {
    // Get current cursor position
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return {csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y};
}


#endif //WINDOWS_PLATFORM
