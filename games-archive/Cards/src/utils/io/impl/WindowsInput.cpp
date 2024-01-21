//
// Created by luxsolari on 1/15/2024.
//
#ifdef WINDOWS_PLATFORM

#include <curses.h>
#include "WindowsInput.h"

void WindowsInput::Update() {
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

bool WindowsInput::IsKeyDown(int key) {
    LockInput();
    bool result = m_keyStates.find(key) != m_keyStates.end();
    UnlockInput();
    return result;
}

bool WindowsInput::IsKeyPressed(int key) {
    LockInput();
    if (m_keyStates.find(key) == m_keyStates.end()) {
        UnlockInput();
        return false;
    } else {
        UnlockInput();
        return true;
    }
}

bool WindowsInput::IsKeyReleased(int key) {
    LockInput();
    bool result = m_prevKeyStates.find(key) != m_prevKeyStates.end() && m_keyStates.find(key) == m_keyStates.end();
    UnlockInput();
    return result;
}

WindowsInput::WindowsInput(bool running) : Input(running) 
{

}

WindowsInput::~WindowsInput() {
    // This destructor is called when the program exits. It will be called before the parent class destructor.
    std::cout << "WindowsInput destructor called" << std::endl;
    m_isRunning = false;
    m_keyStates.clear();
    m_prevKeyStates.clear();
    endwin();
}




#endif //WINDOWS_PLATFORM
