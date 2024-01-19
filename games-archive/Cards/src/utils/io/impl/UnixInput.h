//
// Created by Lux Solari on 19/01/2024.
//

#ifndef CARDS_UNIXINPUT_H
#define CARDS_UNIXINPUT_H
#ifdef UNIX_PLATFORM

#include "../Input.h"

class UnixInput : public Input {
    // Singleton
public:
    static UnixInput *getInstance() {
        static UnixInput instance;
        return &instance;
    }

    void operator=(UnixInput const &) = delete;

    void Update() override;

    bool IsKeyDown(int key) override;

    bool IsKeyPressed(int key) override;

    bool IsKeyReleased(int key) override;
};


#endif //UNIX_PLATFORM
#endif //CARDS_UNIXINPUT_H
