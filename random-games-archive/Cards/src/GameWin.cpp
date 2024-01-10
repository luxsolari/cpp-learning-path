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

const GameWin* GameWin::printAddress() const {
    return this;
}


void GameWin::printClassName() {
    std::cout << "GameWin" << std::endl;
}
