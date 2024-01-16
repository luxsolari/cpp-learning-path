//
// Created by luxsolari on 1/15/2024.
//

#include "../Input.h"

#ifdef WINDOWS_PLATFORM
#ifndef CARDS_WINDOWSINPUT_H
#define CARDS_WINDOWSINPUT_H


class WindowsInput : public Input {
    // Singleton
public:
    static WindowsInput *GetInstance() {
        static WindowsInput instance;
        return &instance;
    }

    void operator=(WindowsInput const &) = delete;

    void Update() override;

    bool IsKeyDown(int key) override;

    bool IsKeyPressed(int key) override;

    bool IsKeyReleased(int key) override;

};


#endif //CARDS_WINDOWSINPUT_H
#endif //WINDOWS_PLATFORM
