//
// Created by luxsolari on 1/15/2024.
//
#include "Output.h"

// Public getters
bool Output::isActive() const { return m_isActive; }
int Output::getCursorX() const { return m_cursorX; }
int Output::getCursorY() const { return m_cursorY; }
int Output::getWidth() const { return m_width; }
int Output::getHeight() const { return m_height; }

// Method to allow modification of console size variables
void Output::setConsoleSize(int width, int height) {
    m_width = width;
    m_height = height;
}

// Method to allow modification of cursor position variables
void Output::setCursorPosition(int x, int y) {
    m_cursorX = x;
    m_cursorY = y;
}

// Method to allow modification of console status
void Output::setActive(bool active) {
    m_isActive = active;
}

// Method to allow modification of console size changed status
void Output::setSizeChanged(bool sizeChanged) {
    m_sizeChanged = sizeChanged;
}

// Method to check if console size has changed
bool Output::hasSizeChanged() const {
    return m_sizeChanged;
}
