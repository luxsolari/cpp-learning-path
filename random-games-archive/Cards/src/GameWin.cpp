//
// Created by luxsolari on 09/01/2024.
//
#ifdef WINDOWS_PLATFORM
#include <iostream>
#include <thread>
#include "GameWin.h"

GameWin::GameWin() = default;

GameWin::~GameWin() = default;

const GameWin* GameWin::getInstance() {
    static const GameWin instance;
    // wait for 1 second
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // get the current time as seconds since epoch
    auto now = std::chrono::steady_clock::now();
    // get the difference between now and the time the instance was created
    auto diff = now - instance.created_at;
    // get the difference in seconds
    auto diff_sec = std::chrono::duration_cast<std::chrono::seconds>(diff);
    return &instance;
}

const GameWin* GameWin::printAddress() const {
    return this;
}

void GameWin::printClassName() {
    std::cout << "GameWin" << std::endl;
}
#endif //WINDOWS_PLATFORM
