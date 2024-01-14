//
// Created by Lux Solari on 12/01/2024.
//

#ifdef UNIX_PLATFORM
#ifndef CARDS_UNIXCONSOLE_H
#define CARDS_UNIXCONSOLE_H
#include "Console.h"

class UnixConsole : public Console {
public:
// Singleton
    UnixConsole() = default;
    ~UnixConsole() override = default;
    UnixConsole(const UnixConsole&) = delete;
    UnixConsole(UnixConsole&&) = delete;
    UnixConsole& operator=(const UnixConsole&) = delete;
    UnixConsole& operator=(UnixConsole&&) = delete;
    static const UnixConsole* getInstance();

    // Methods
    const UnixConsole* getAddress() const override;
    std::vector<int> getConsoleSize() const override;
    std::vector<int> getCursorPosition() const override;
    void printToConsole(const char *format, ...) const override;
    void printToConsoleAtLocation(int y, int x, const char *format, ...) const override;
    void setConsoleSize(int width, int height) const override;
    void setCursorPosition(int x, int y) const override;
    void moveCursorUp(int steps) const override;
    void moveCursorDown(int steps) const override;
    void moveCursorLeft(int steps) const override;
    void moveCursorRight(int steps) const override;
    void returnCursorToStart() const override;
    void returnCarriage() const override;
    void clearScreen() const override;
    void drawSquareBorder(int width, int height, std::vector<int> startPos) const override;
    void printClassName() const override;
    void waitEnterKey() const override;
private:
    // ncurses wrapper
};

#endif //CARDS_UNIXCONSOLE_H
#endif //UNIX_PLATFORM
