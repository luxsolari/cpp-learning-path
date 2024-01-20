//
// Created by luxsolari on 1/15/2024.
//
#include "Input.h"

Input::Input(bool running) : m_isRunning(running)
{
    Start(); // Start the input thread
}

Input::~Input() {
    std::cout << "Input destructor called" << std::endl;
    Stop();  // Ensure the input thread is stopped before exiting
}

void Input::Start() {
    m_inputThread = std::thread(&Input::InputThreadFunction, this);
}

void Input::Stop() {
    m_isRunning = false;
    if (m_inputThread.joinable()) {
        m_inputThread.join();
    }
}

void Input::InputThreadFunction() {
    // reset key states
    for (int key = 0; key < 256; ++key) {
        m_keyStates[key] = false;
        m_prevKeyStates[key] = false;
    }

    while (m_isRunning) {
        Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));  // Adjust as needed
    }
}
