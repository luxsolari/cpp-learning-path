//
// Created by luxsolari on 1/15/2024.
//

#ifndef CARDS_GAMEMANAGERFACTORY_H
#define CARDS_GAMEMANAGERFACTORY_H


#include "../GameManager.h"

class GameManagerFactory {
public:
    // Singleton
    GameManagerFactory() = delete;
    GameManagerFactory(const GameManagerFactory&) = delete;
    GameManagerFactory& operator=(const GameManagerFactory&) = delete;
    GameManagerFactory(GameManagerFactory&&) = delete;
    GameManagerFactory& operator=(GameManagerFactory&&) = delete;
    ~GameManagerFactory() = delete;

    // Factory
    static GameManager* createGameManager();

};


#endif //CARDS_GAMEMANAGERFACTORY_H
