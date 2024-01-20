//
// Created by luxsolari on 12/01/2024.
//

#ifndef CARDS_CONSOLE_H
#define CARDS_CONSOLE_H
#include <thread>
#include <mutex>

class Output {
public:
    // Singleton
    static Output* getInstance();

protected:
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

#endif //CARDS_CONSOLE_H
