//
// Created by luxsolari on 1/15/2024.
//

#ifndef CARDS_INPUT_H
#define CARDS_INPUT_H
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>

class Input {
public:
    explicit Input(bool running);
    Input(const Input&) = delete;
    Input(Input&&) = delete;
    Input& operator=(const Input&) = delete;
    Input& operator=(Input&&) = delete;
    virtual ~Input();

    void Start();
    void Stop();
    void InputThreadFunction();
    virtual void Update() = 0;
    virtual bool IsKeyDown(int key) = 0;
    virtual bool IsKeyPressed(int key) = 0;
    virtual bool IsKeyReleased(int key) = 0;
protected:
    std::unordered_set<int> m_keyStates = {};
    std::unordered_set<int> m_prevKeyStates = {};
    bool m_isRunning;
    std::thread m_inputThread;
    mutable std::mutex m_inputMutex;

    void LockInput() const {
        m_inputMutex.lock();
    }

    void UnlockInput() const {
        m_inputMutex.unlock();
    }
};


#endif //CARDS_INPUT_H
