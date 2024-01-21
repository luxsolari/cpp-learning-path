//
// Created by luxsolari on 09/01/2024.
//
#ifdef WINDOWS_PLATFORM

#include <iostream>
#include <curses.h>
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

}

void WindowsOutput::BeginDraw() {

}

void WindowsOutput::Draw() {

}

void WindowsOutput::EndDraw() {

}

void WindowsOutput::Setup() {
    // Any setup operations for the output should be done here.
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);

    // Start the output thread. This should be called last.
    this->Start();
}

void WindowsOutput::Cleanup() {
    // Any cleanup operations for the output should be done here.
    this->m_isRunning = false;
    endwin();
    // Stop the output thread. This should be called last.
    this->Stop();
}

#endif //WINDOWS_PLATFORM
