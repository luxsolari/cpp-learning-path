//
// Created by luxsolari on 1/15/2024.
//
#ifdef WINDOWS_PLATFORM

#include <Windows.h>
#include "WindowsInput.h"

void WindowsInput::Update() {
    LockInput();  // Lock the mutex before accessing shared data

    m_prevKeyStates = m_keyStates;

    for (int key = 0; key < 256; ++key) {
        m_keyStates[key] = GetAsyncKeyState(key) & 0x8000; // Check if key is pressed
    }

    UnlockInput();  // Unlock the mutex after updating shared data
}

bool WindowsInput::IsKeyDown(int key) {
    LockInput();
    bool result = m_keyStates.find(key) != m_keyStates.end() && m_keyStates.at(key);
    UnlockInput();
    return result;
}

bool WindowsInput::IsKeyPressed(int key) {
    LockInput();
    bool result = m_keyStates.find(key) != m_keyStates.end() && !m_prevKeyStates[key] && m_keyStates[key];
    UnlockInput();
    return result;
}

bool WindowsInput::IsKeyReleased(int key) {
    LockInput();
    bool result = m_keyStates.find(key) != m_keyStates.end() && m_prevKeyStates[key] && !m_keyStates[key];
    UnlockInput();
    return result;
}

WindowsInput::WindowsInput(bool running) : Input(running) {}

WindowsInput::~WindowsInput() {
    // This destructor is called when the program exits. It will be called before the parent class destructor.
    std::cout << "WindowsInput destructor called" << std::endl;
    m_isRunning = false;
    m_keyStates.clear();
    m_prevKeyStates.clear();
}

#endif //WINDOWS_PLATFORM
