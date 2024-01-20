//
// Created by Lux Solari on 19/01/2024.
//

#ifndef CARDS_UNIXINPUT_H
#define CARDS_UNIXINPUT_H
#ifdef UNIX_PLATFORM

#include "../Input.h"

class UnixInput final : public Input {
    // Singleton
public:
    explicit UnixInput(bool running);
    UnixInput(UnixInput const &) = delete;
    UnixInput(UnixInput&&) = delete;
    UnixInput& operator=(UnixInput const &) = delete;
    UnixInput& operator=(UnixInput&&) = delete;
    ~UnixInput() final;

    static UnixInput *getInstance(bool running) {
        static UnixInput instance(running);
        return &instance;
    }

    void Update() override;

    bool IsKeyDown(int key) override;

    bool IsKeyPressed(int key) override;
    bool IsKeyReleased(int key) override;
};


#endif //UNIX_PLATFORM
#endif //CARDS_UNIXINPUT_H
