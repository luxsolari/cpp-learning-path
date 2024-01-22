//
// Created by luxsolari on 09/01/2024.
//
#ifdef WINDOWS_PLATFORM

#include <iostream>
#include <curses.h>
#include <panel.h>
#include <Windows.h>
#include "WindowsOutput.h"

WindowsOutput::WindowsOutput(bool running) : Output(running)
{
    this->Setup(); // Setup operations for the output
}

WindowsOutput::~WindowsOutput()
{
    std::cout << "WindowsOutput destructor called" << std::endl;
    this->Cleanup(); // Cleanup operations for the output
}

void WindowsOutput::Update() {
    // keep track of console window diemnsion
    m_height = getmaxy(stdscr);
    m_width  = getmaxx(stdscr);
}

void WindowsOutput::BeginDraw() {
    LockOutput();

    // clear screen
    clear();
    //resize_term(0,0);

    UnlockOutput();
}

void WindowsOutput::Draw() {
    // Draw the output here.
	attron(COLOR_PAIR(1));
	// check if terminal is big enough
    if (m_width < 80 || m_height < 24) {
		mvprintw(m_height / 2, (m_width - 25) / 2, "Please resize your terminal");
		mvprintw((m_height / 2) + 1, (m_width - 25) / 2, "and press any key to continue");
    }
    else {
        // print title
        mvprintw(0, (m_width - 25) / 2, "Welcome to the game!");
        // print menu
        mvprintw(2, (m_width - 25) / 2, "1. Start game");
        mvprintw(3, (m_width - 25) / 2, "2. Options");
        mvprintw(4, (m_width - 25) / 2, "3. Exit");
        // print cursor
        mvprintw(2 + 0, (m_width - 25) / 2 - 2, ">");
    }
}

void WindowsOutput::EndDraw() {
    refresh();
}

void WindowsOutput::Setup() {
    // Any setup operations for the output should be done here.
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    //resize_term(0,0);
    curs_set(0);
    start_color();

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);

    // Initialize dimensions
    m_width = getmaxx(stdscr);
    m_height = getmaxy(stdscr);

    // Create the output thread.
    m_outputThread = std::thread(&Output::OutputThreadFunction, this);
}

void WindowsOutput::Cleanup() {
    // Any cleanup operations for the output should be done here.
    endwin();

}

#endif //WINDOWS_PLATFORM
