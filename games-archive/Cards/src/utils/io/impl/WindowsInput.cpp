//
// Created by luxsolari on 1/15/2024.
//
#ifdef WINDOWS_PLATFORM

#include <Windows.h>
#include "WindowsInput.h"

void WindowsInput::Update() {
    LockInput();  // Lock the mutex before accessing shared data

    prevKeyStates = keyStates;

    for (int key = 0; key < 256; ++key) {
        keyStates[key] = GetAsyncKeyState(key) & 0x8000; // Check if key is pressed
    }

    UnlockInput();  // Unlock the mutex after updating shared data
}

bool WindowsInput::IsKeyDown(int key) {
    LockInput();
    bool result = keyStates.find(key) != keyStates.end() && keyStates.at(key);
    UnlockInput();
    return result;
}

bool WindowsInput::IsKeyPressed(int key) {
    LockInput();
    bool result = keyStates.find(key) != keyStates.end() && !prevKeyStates[key] && keyStates[key];
    UnlockInput();
    return result;
}

bool WindowsInput::IsKeyReleased(int key) {
    LockInput();
    bool result = keyStates.find(key) != keyStates.end() && prevKeyStates[key] && !keyStates[key];
    UnlockInput();
    return result;
}
#endif //WINDOWS_PLATFORM
