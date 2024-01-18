//
// Created by luxsolari on 09/01/2024.
//
#ifdef WINDOWS_PLATFORM
#ifndef CARDS_GAMEWIN_H
#define CARDS_GAMEWIN_H
#include <vector>
#include "../Output.h"

class WindowsOutput : public Output {
public:
    // Singleton
    WindowsOutput() = default;
    ~WindowsOutput() override = default;
    WindowsOutput(const WindowsOutput&) = delete;
    WindowsOutput(WindowsOutput&&) = delete;
    WindowsOutput& operator=(const WindowsOutput&) = delete;
    WindowsOutput& operator=(WindowsOutput&&) = delete;
    static WindowsOutput* getInstance();

    // Methods
    const WindowsOutput* getAddress() const override;
    std::vector<int> getConsoleSize() const override;
    std::vector<int> getCursorPosition() const override;
    void printToConsole(const char *format, ...) const override;
    void printToConsoleWide(const wchar_t *format, ...) const override;
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

};


#endif //CARDS_GAMEWIN_H
#endif //WINDOWS_PLATFORM
