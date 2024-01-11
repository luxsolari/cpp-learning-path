//
// Created by luxsolari on 09/01/2024.
//

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

