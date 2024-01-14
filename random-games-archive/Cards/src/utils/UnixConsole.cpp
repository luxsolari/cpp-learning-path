//
// Created by Lux Solari on 12/01/2024.
//

#ifdef UNIX_PLATFORM
#include <iostream>
#include "UnixConsole.h"

const UnixConsole *UnixConsole::getInstance() {
    static const UnixConsole instance;
    return &instance;
}

const UnixConsole *UnixConsole::getAddress() const {
    return this;
}

std::vector<int> UnixConsole::getConsoleSize() const {
    // get console size using ncurses
    return this->m_ncursesWrapper->getConsoleSize();
}

std::vector<int> UnixConsole::getCursorPosition() const {
    return this->m_ncursesWrapper->getCursorPosition();
}

void UnixConsole::setConsoleSize(int width, int height) const {

}

void UnixConsole::setCursorPosition(int x, int y) const {

}

void UnixConsole::moveCursorUp(int steps) const {

}

void UnixConsole::moveCursorDown(int steps) const {

}

void UnixConsole::moveCursorLeft(int steps) const {

}

void UnixConsole::moveCursorRight(int steps) const {

}

void UnixConsole::returnCursorToStart() const {

}

void UnixConsole::returnCarriage() const {

}

void UnixConsole::clearScreen() const {

}

void UnixConsole::drawSquareBorder(int width, int height, std::vector<int> startPos) const {

}

void UnixConsole::printClassName() const {
}

void UnixConsole::printToConsole(const char *format, ...) const {
    this->m_ncursesWrapper->printToConsole(format);
    this->m_ncursesWrapper->refreshScreen();
}


void UnixConsole::printToConsoleAtLocation(int y, int x, const char *format, ...) const {
    this->m_ncursesWrapper->printToConsoleAtLocation(y, x, format);
    this->m_ncursesWrapper->refreshScreen();
}

void UnixConsole::waitEnterKey() const {
    this->m_ncursesWrapper->waitEnterKey();
}

void UnixConsole::printToConsoleWide(const wchar_t *format, ...) const {

}

#endif //UNIX_PLATFORM
