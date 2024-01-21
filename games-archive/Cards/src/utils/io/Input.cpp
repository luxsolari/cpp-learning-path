//
// Created by luxsolari on 1/15/2024.
//
#include "Input.h"

Input::Input(bool running) : m_isRunning(running)
{

}

Input::~Input()
{

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
    m_keyStates.clear();
    m_prevKeyStates.clear();

    while (m_isRunning) {
        Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));  // Adjust as needed
    }
}
