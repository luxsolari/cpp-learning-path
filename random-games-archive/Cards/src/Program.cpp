#include <ncurses.h>
#include <ios>

int main() {
    setlocale(LC_ALL, "C/UTF-8/C/C/C/C");
    initscr();
    cbreak(); // disable line buffering
    noecho(); // disable echoing
    //raw(); // disable line buffering and ctrl+c
    keypad(stdscr, TRUE); // enable function keys
    curs_set(0); // disable cursor
    int height, width, start_y, start_x;
    height = 6;
    width = 8;
    start_y = start_x = 10;

    // init color pairs
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    WINDOW* CARD = newwin(height, width, start_y, start_x);
    wbkgd(CARD, COLOR_PAIR(2));
    refresh();

    box(CARD, 0,0);

    // card suit symbols (unicode)
    // Define card suits symbols glyphs for *nix, full width unicode characters
    const std::string SPADE = "\u2660";
    const std::string CLUB = "\u2663";
    const std::string HEART = "\u2665";
    const std::string DIAMOND = "\u2666";

    mvwprintw(CARD, 1, 3, "%s", SPADE.c_str());
    mvwprintw(CARD, 1, 1, "10");
    mvwprintw(CARD, 4, 6, "%s", SPADE.c_str());
    mvwprintw(CARD, 4, 4, "10");
    wrefresh(CARD);

    getch();
    endwin();
    return 0;
}
