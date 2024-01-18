//
// Created by luxsolari on 1/15/2024.
//
#include "Input.h"

Input::Input() : running(true) {

}

Input::~Input() {
    Stop();  // Ensure the input thread is stopped before exiting
}

void Input::Start() {
    inputThread = std::thread(&Input::InputThreadFunction, this);
}

void Input::Stop() {
    running = false;
    if (inputThread.joinable()) {
        inputThread.join();
    }
}

void Input::InputThreadFunction() {
    // reset key states
    for (int key = 0; key < 256; ++key) {
        keyStates[key] = false;
        prevKeyStates[key] = false;
    }

    while (running) {
        Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));  // Adjust as needed
    }
}
