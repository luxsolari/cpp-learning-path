//
// Created by luxsolari on 09/01/2024.
//

#include <iostream>
#include "GameWin.h"

GameWin::GameWin() = default;

GameWin::~GameWin() = default;

GameWin *GameWin::getInstance() {
    static GameWin instance;
    return &instance;
}

void GameWin::printName() {
    // Print address of the instance
    std::cout << "GameWin instance address: " << this << std::endl;
}
