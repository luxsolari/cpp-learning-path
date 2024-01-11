//
// Created by luxsolari on 09/01/2024.
//
#ifdef UNIX_PLATFORM
#include <iostream>
#include "GameUnix.h"

GameUnix::GameUnix() = default;

GameUnix::~GameUnix() = default;

const GameUnix* GameUnix::getInstance() {
    static const GameUnix instance;
    return &instance;
}

const GameUnix* GameUnix::printAddress() const {
    return this;
}

void GameUnix::printClassName() {
    std::cout << "GameUnix" << std::endl;
}

std::string GameUnix::getConsoleSize() {
    // return size of console window
    return "Not implemented yet";
}

#endif //UNIX_PLATFORM