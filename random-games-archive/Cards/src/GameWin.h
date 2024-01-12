//
// Created by luxsolari on 09/01/2024.
//
#ifdef WINDOWS_PLATFORM
#ifndef CARDS_GAMEWIN_H
#define CARDS_GAMEWIN_H
#include <vector>

class GameWin {
public:
    GameWin();
    ~GameWin();
    // Singleton
    static const GameWin* getInstance();

    // Methods

    // Diagnostic method
    const GameWin* printAddress() const;
    std::vector<int> getConsoleSize() const;
    std::vector<int> getCursorPosition() const;
    void setConsoleSize(int width, int height) const;
    void setCursorPosition(int x, int y) const;
    void moveCursorUp(int steps) const;
    void moveCursorDown(int steps) const;
    void moveCursorLeft(int steps) const;
    void moveCursorRight(int steps) const;
    void returnCursorToStart() const;
    void returnCarriage() const;
    void clearScreen() const;
    void drawBorder(int width, int height) const;
    void drawCard(int x, int y, int width, int height) const;
    void printClassName();

};


#endif //CARDS_GAMEWIN_H
#endif //WINDOWS_PLATFORM
