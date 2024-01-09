//
// Created by luxsolari on 09/01/2024.
//

#include <iostream>
#include "GameUnix.h"

GameUnix::GameUnix() = default;

GameUnix::~GameUnix() = default;

GameUnix *GameUnix::getInstance() {
    static GameUnix instance;
    return &instance;
}

void GameUnix::printName() {
    // Print address of the instance
    std::cout << "GameUnix instance address: " << this << std::endl;
}

