//
// Created by luxsolari on 09/01/2024.
//
#ifdef UNIX_PLATFORM
#ifndef CARDS_GAMEUNIX_H
#define CARDS_GAMEUNIX_H


class GameUnix {
public:
    GameUnix();
    ~GameUnix();
    // Singleton
    static const GameUnix* getInstance();

    // Methods

    // Diagnostic method
    [[nodiscard]] const GameUnix* printAddress() const;
    [[nodiscard]] static std::string getConsoleSize();
    static void printClassName();
};


#endif //CARDS_GAMEUNIX_H
#endif //UNIX_PLATFORM
