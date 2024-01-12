//
// Created by luxsolari on 12/01/2024.
//

#ifndef CARDS_CONSOLE_H
#define CARDS_CONSOLE_H
#include <vector>

class Console {
public:
    virtual ~Console() = default;
    virtual const class WindowsConsole* printAddress() const = 0;
    virtual std::vector<int> getConsoleSize() const = 0;
    virtual std::vector<int> getCursorPosition() const = 0;
    virtual void setConsoleSize(int width, int height) const = 0;
    virtual void setCursorPosition(int x, int y) const = 0;
    virtual void moveCursorUp(int steps) const = 0;
    virtual void moveCursorDown(int steps) const = 0;
    virtual void moveCursorLeft(int steps) const = 0;
    virtual void moveCursorRight(int steps) const = 0;
    virtual void returnCursorToStart() const = 0;
    virtual void returnCarriage() const = 0;
    virtual void clearScreen() const = 0;
    virtual void drawSquareBorder(int width, int height, std::vector<int> startPos) const = 0;
    virtual void printClassName() = 0;

// Variables
protected:
    // cursor position
    int m_cursorX{0};
    int m_cursorY{0};
    // console size
    int m_width{0};
    int m_height{0};
};


#endif //CARDS_CONSOLE_H
