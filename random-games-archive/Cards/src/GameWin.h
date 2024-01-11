//
// Created by luxsolari on 09/01/2024.
//

#ifdef WINDOWS_PLATFORM
#ifndef CARDS_GAMEWIN_H
#define CARDS_GAMEWIN_H
#include <chrono>

class GameWin {
public:
    GameWin();
    ~GameWin();
    // Singleton
    static const GameWin* getInstance();

    // Methods

    // Diagnostic method
    [[nodiscard]] const GameWin* printAddress() const;
    static void printClassName();

    // Member variables
    std::chrono::steady_clock::time_point created_at{std::chrono::steady_clock::now()};

};


#endif //CARDS_GAMEWIN_H
#endif //WINDOWS_PLATFORM
