#include <clocale>
#include <iostream>
#include <ncurses.h>

int main() {
    // get terminal type
    char *termType = getenv("TERM");
    std::cout << "Terminal type: " << termType << std::endl;
    // set locale
    setlocale(LC_ALL, "C/UTF-8/C/C/C/C");

    initscr();  // Initialize curses mode
    start_color();  // Enable color support if needed
    raw();  // Disable line buffering
    keypad(stdscr, TRUE);  // Enable special keys
    noecho();  // Don't display pressed keys

    // draw border around screen
    box(stdscr, 0, 0);

    // set invisible cursor
    curs_set(0);

    // get screen size
    int x{0};
    int y{0};
    getmaxyx(stdscr, y, x);
    std::string message = "Hello, world!";

    // print on center of screen
    mvprintw(y / 2, (x / 2) - (message.length() / 2), "Hello, world!");
    mvprintw(y / 2, (x / 2) - (message.length() / 2), "  ♠︎ ♣︎ ♥︎ ♦︎  ");

    // refresh screen
    refresh();
    // wait for enter key
    std::wcin.get();

    // end ncurses
    endwin();

    return 0;
}
