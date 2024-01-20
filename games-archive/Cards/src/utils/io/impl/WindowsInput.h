//
// Created by luxsolari on 1/15/2024.
//

#include "../Input.h"

#ifdef WINDOWS_PLATFORM
#ifndef CARDS_WINDOWSINPUT_H
#define CARDS_WINDOWSINPUT_H


class WindowsInput final : public Input {
public:
    // Singleton
    explicit WindowsInput(bool running);
    WindowsInput(WindowsInput const &) = delete;
    WindowsInput(WindowsInput&&) = delete;
    WindowsInput& operator=(WindowsInput const &) = delete;
    WindowsInput& operator=(WindowsInput&&) = delete;
    ~WindowsInput() final;

    static WindowsInput *GetInstance(bool running) {
        static WindowsInput instance(running);
        return &instance;
    }

    void Update() override;

    bool IsKeyDown(int key) override;

    bool IsKeyPressed(int key) override;
    bool IsKeyReleased(int key) override;
private:
};


#endif //CARDS_WINDOWSINPUT_H
#endif //WINDOWS_PLATFORM
