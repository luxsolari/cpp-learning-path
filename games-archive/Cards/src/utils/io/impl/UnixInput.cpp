//
// Created by Lux Solari on 19/01/2024.
//
#ifdef UNIX_PLATFORM
#include "UnixInput.h"
#include <ncurses.h>

void UnixInput::Update() {
    LockInput();  // Lock the mutex before accessing shared data
    static int cycles = 0;
    mvprintw(0, 0, "Listening for input... %d\n", cycles++);
    m_prevKeyStates = m_keyStates;

    int ch {};
    while ((ch = wgetch(stdscr)) != ERR) {
        // Verify if the key is in the map
        if (m_keyStates.find(ch) == m_keyStates.end()) {
            m_keyStates.insert(ch);
        }
    }

    // Remove keys that are no longer pressed after 10 cycles.
    // This is to prevent keys from being stuck in the map forever.
    if (cycles % 10 == 0) {
        for (auto it = m_keyStates.begin(); it != m_keyStates.end();) {
            if (m_prevKeyStates.find(*it) == m_prevKeyStates.end()) {
                it = m_keyStates.erase(it);
            } else {
                ++it;
            }
        }
    }


    UnlockInput();  // Unlock the mutex after updating shared data
}

bool UnixInput::IsKeyDown(int key) {
    LockInput();
    bool result = m_keyStates.find(key) != m_keyStates.end();
    UnlockInput();
    return result;
}

bool UnixInput::IsKeyPressed(int key) {
    LockInput();
    if (m_keyStates.find(key) == m_keyStates.end()) {
        UnlockInput();
        return false;
    } else {
        UnlockInput();
        return true;
    }
}

bool UnixInput::IsKeyReleased(int key) {
    LockInput();
    bool result = m_prevKeyStates.find(key) != m_prevKeyStates.end() && m_keyStates.find(key) == m_keyStates.end();
    UnlockInput();
    return result;
}

UnixInput::UnixInput(bool running) : Input(running) {
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);
}

UnixInput::~UnixInput() {
    // This destructor is called when the program exits. It will be called before the parent class destructor.
    std::cout << "UnixInput destructor called" << std::endl;
    m_isRunning = false;
    m_keyStates.clear();
    m_prevKeyStates.clear();
    endwin();
}

#endif //UNIX_PLATFORM
