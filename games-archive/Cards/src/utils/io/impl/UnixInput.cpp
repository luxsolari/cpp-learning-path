//
// Created by Lux Solari on 19/01/2024.
//
#ifdef UNIX_PLATFORM
#include "UnixInput.h"
#include <ncurses.h>

void UnixInput::Update() {
    LockInput();  // Lock the mutex before accessing shared data

    m_prevKeyStates = m_keyStates;

    for (int key = 0; key < 256; ++key) {
        int ch = has_key(key);
        if (ch != ERR) {
            m_keyStates[key] = ch & 0x8000; // Check if key is pressed
        }
    }

    UnlockInput();  // Unlock the mutex after updating shared data
}

bool UnixInput::IsKeyDown(int key) {
    LockInput();
    bool result = m_keyStates.find(key) != m_keyStates.end() && m_keyStates.at(key);
    UnlockInput();
    return result;
}

bool UnixInput::IsKeyPressed(int key) {
    LockInput();
    bool result = m_keyStates.find(key) != m_keyStates.end() && !m_prevKeyStates[key] && m_keyStates[key];
    UnlockInput();
    return result;
}

bool UnixInput::IsKeyReleased(int key) {
    LockInput();
    bool result = m_keyStates.find(key) != m_keyStates.end() && m_prevKeyStates[key] && !m_keyStates[key];
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
