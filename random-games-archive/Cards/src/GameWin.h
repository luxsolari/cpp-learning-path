//
// Created by luxsolari on 09/01/2024.
//

#ifndef CARDS_GAMEWIN_H
#define CARDS_GAMEWIN_H


class GameWin {
public:
    GameWin();
    ~GameWin();
    // Singleton
    static GameWin* getInstance();

    // Methods

    // Diagnostic method
    void printName();
};


#endif //CARDS_GAMEWIN_H
