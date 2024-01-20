//
// Created by luxsolari on 09/01/2024.
//
#ifdef WINDOWS_PLATFORM
#ifndef CARDS_GAMEWIN_H
#define CARDS_GAMEWIN_H
#include "../Output.h"

class WindowsOutput : public Output {
public:
    // Singleton
    static WindowsOutput* getInstance();
};

#endif //CARDS_GAMEWIN_H
#endif //WINDOWS_PLATFORM
