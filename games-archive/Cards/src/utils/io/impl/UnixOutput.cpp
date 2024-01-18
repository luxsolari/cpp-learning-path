//
// Created by Lux Solari on 12/01/2024.
//

#ifdef UNIX_PLATFORM
#include <iostream>
#include "UnixOutput.h"

UnixOutput *UnixOutput::getInstance() {
    static UnixOutput instance;
    return &instance;
}

const UnixOutput *UnixOutput::getAddress() const {
    return this;
}

std::vector<int> UnixOutput::getConsoleSize() const {
    // get console size using ncurses
    return this->m_ncursesWrapper->getConsoleSize();
}

std::vector<int> UnixOutput::getCursorPosition() const {
    return this->m_ncursesWrapper->getCursorPosition();
}

void UnixOutput::setConsoleSize(int width, int height) const {

}

void UnixOutput::setCursorPosition(int x, int y) const {

}

void UnixOutput::moveCursorUp(int steps) const {

}

void UnixOutput::moveCursorDown(int steps) const {

}

void UnixOutput::moveCursorLeft(int steps) const {

}

void UnixOutput::moveCursorRight(int steps) const {

}

void UnixOutput::returnCursorToStart() const {

}

void UnixOutput::returnCarriage() const {

}

void UnixOutput::clearScreen() const {

}

void UnixOutput::drawSquareBorder(int width, int height, std::vector<int> startPos) const {

}

void UnixOutput::printClassName() const {
}

void UnixOutput::printToConsole(const char *format, ...) const {
    this->m_ncursesWrapper->printToConsole(format);
    this->m_ncursesWrapper->refreshScreen();
}


void UnixOutput::printToConsoleAtLocation(int y, int x, const char *format, ...) const {
    this->m_ncursesWrapper->printToConsoleAtLocation(y, x, format);
    this->m_ncursesWrapper->refreshScreen();
}

void UnixOutput::printToConsoleWide(const wchar_t *format, ...) const {

}

#endif //UNIX_PLATFORM
