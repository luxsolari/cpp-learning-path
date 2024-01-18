//
// Created by luxsolari on 1/15/2024.
//

#ifndef CARDS_INPUT_H
#define CARDS_INPUT_H
#include <iostream>
#include <unordered_map>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>

class Input {
public:
    Input();
    virtual ~Input();
    void Start();
    void Stop();
    void InputThreadFunction();
    virtual void Update() = 0;
    virtual bool IsKeyDown(int key) = 0;
    virtual bool IsKeyPressed(int key) = 0;
    virtual bool IsKeyReleased(int key) = 0;
protected:
    std::unordered_map<int, bool> keyStates;
    std::unordered_map<int, bool> prevKeyStates;
    bool running;
    std::thread inputThread;
    mutable std::mutex inputMutex;

    void LockInput() const {
        inputMutex.lock();
    }

    void UnlockInput() const {
        inputMutex.unlock();
    }
};


#endif //CARDS_INPUT_H
