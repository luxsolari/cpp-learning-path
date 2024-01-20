//
// Created by Lux Solari on 12/01/2024.
//
#ifdef UNIX_PLATFORM
#ifndef CARDS_UNIXCONSOLE_H
#define CARDS_UNIXCONSOLE_H
#include "../Output.h"

class UnixOutput : public Output {
public:
    // Singleton
    static UnixOutput* getInstance();
};

#endif //CARDS_UNIXCONSOLE_H
#endif //UNIX_PLATFORM
