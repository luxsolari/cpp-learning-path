//
// Created by luxsolari on 12/01/2024.
//

#ifndef CARDS_CONSOLE_H
#define CARDS_CONSOLE_H
#include <vector>
#include <memory>

#ifdef UNIX_PLATFORM
#include <ncurses.h>

class NcursesWrapper {
public:
    NcursesWrapper() {
        initscr(); // Initialize ncurses
    }

    ~NcursesWrapper() {
        endwin(); // End ncurses
    }

    void printToConsole(const char *format, ...) const {
        va_list args;
        va_start(args, format);
        ::printw(format, args); // Use :: to refer to the global namespace
        va_end(args);
    }

    // Add wrapper functions for other ncurses functions
    void printToConsoleAtLocation(int y, int x, const char *format, ...) const {
        va_list args;
        va_start(args, format);
        ::mvprintw(y, x, format, args); // Use :: to refer to the global namespace
        va_end(args);
    }

    // Add more wrapper functions or classes as needed
    // refresh wrapper
    void refreshScreen() const {
        ::refresh();
    }

    // getch wrapper
    int waitAnyChar() const {
        return ::getch();
    }

    // get console size
    std::vector<int> getConsoleSize() const {
        int x{0};
        int y{0};
        getmaxyx(stdscr, y, x);
        return std::vector<int>{x, y};
    }

    // get cursor position
    std::vector<int> getCursorPosition() const {
        int x{0};
        int y{0};
        getyx(stdscr, y, x);
        return std::vector<int>{x, y};
    }

    // wait for enter key
    void waitEnterKey() const {
        ::getch();
    }
};
#endif //UNIX_PLATFORM

class Output {
public:
    virtual ~Output() = default;

    // Virtual methods to be implemented by derived classes
    virtual const class Output* getAddress() const = 0;
    virtual std::vector<int> getConsoleSize() const = 0;
    virtual std::vector<int> getCursorPosition() const = 0;
    virtual void printToConsole(const char *format, ...) const = 0;
    virtual void printToConsoleWide(const wchar_t *format, ...) const = 0;
    virtual void printToConsoleAtLocation(int y, int x, const char *format, ...) const = 0;
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
    virtual void printClassName() const = 0;

    // Public getters
    bool isActive() const;
    int getCursorX() const;
    int getCursorY() const;
    int getWidth() const;
    int getHeight() const;
    // Method to allow modification of console size variables
    void setConsoleSize(int width, int height);
    // Method to allow modification of cursor position variables
    void setCursorPosition(int x, int y);
    // Method to allow modification of console status
    void setActive(bool active);
    // Method to allow modification of console size changed status
    void setSizeChanged(bool sizeChanged);
    // Method to check if console size has changed
    bool hasSizeChanged() const;

// Variables
protected:
    // status
    bool m_isActive{false}; // is console active?
    bool m_sizeChanged{false}; // has console size changed?

    // cursor position
    int m_cursorX{0};
    int m_cursorY{0};
    // console size
    int m_width{0};
    int m_height{0};

#ifdef UNIX_PLATFORM
    // ncurses wrapper
    std::unique_ptr<NcursesWrapper> m_ncursesWrapper{std::unique_ptr<NcursesWrapper>(new NcursesWrapper())};
#endif //UNIX_PLATFORM
};

#endif //CARDS_CONSOLE_H
