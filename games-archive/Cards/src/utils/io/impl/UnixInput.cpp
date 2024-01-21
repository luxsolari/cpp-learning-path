//
// Created by Lux Solari on 19/01/2024.
//
#ifdef UNIX_PLATFORM
#include "UnixInput.h"
#include <ncurses.h>

void UnixInput::Update() {
    LockInput();  // Lock the mutex before accessing shared data
    static int counter = 0;
    printw("Listening for input... %d\n", counter ++ );
    m_prevKeyStates = m_keyStates;

    for (int key = 0; key < 512; ++key) {
        int ch = wgetch(stdscr);
        if (ch != ERR) {
            // Verify if the key is in the map
            if (m_keyStates.find(ch) != m_keyStates.end()) {
                m_keyStates[ch] = true;
            }
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

std::vector<int> UnixInput::GetPressedKeys() {
    std::vector<int> pressedKeys;
    for (int key = 0; key < 512; ++key) {
        if (this->m_prevKeyStates[key]) {
            pressedKeys.push_back(key);
        }
    }
    return pressedKeys;
}

#endif //UNIX_PLATFORM
