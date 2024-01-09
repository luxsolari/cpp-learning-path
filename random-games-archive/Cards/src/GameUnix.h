//
// Created by luxsolari on 09/01/2024.
//

#ifndef CARDS_GAMEUNIX_H
#define CARDS_GAMEUNIX_H


class GameUnix {
public:
    GameUnix();
    ~GameUnix();
    // Singleton
    static GameUnix* getInstance();

    // Methods

    // Diagnostic method
    void printName();
};


#endif //CARDS_GAMEUNIX_H
