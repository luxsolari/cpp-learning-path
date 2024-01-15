//
// Created by luxsolari on 1/15/2024.
//
#include "Console.h"

// Public getters
bool Console::isActive() const { return m_isActive; }
int Console::getCursorX() const { return m_cursorX; }
int Console::getCursorY() const { return m_cursorY; }
int Console::getWidth() const { return m_width; }
int Console::getHeight() const { return m_height; }

// Method to allow modification of console size variables
void Console::setConsoleSize(int width, int height) {
    m_width = width;
    m_height = height;
}

// Method to allow modification of cursor position variables
void Console::setCursorPosition(int x, int y) {
    m_cursorX = x;
    m_cursorY = y;
}

// Method to allow modification of console status
void Console::setActive(bool active) {
    m_isActive = active;
}

// Method to allow modification of console size changed status
void Console::setSizeChanged(bool sizeChanged) {
    m_sizeChanged = sizeChanged;
}

// Method to check if console size has changed
bool Console::hasSizeChanged() const {
    return m_sizeChanged;
}
