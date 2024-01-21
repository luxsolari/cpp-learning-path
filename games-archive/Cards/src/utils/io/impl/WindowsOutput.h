//
// Created by luxsolari on 09/01/2024.
//
#ifdef WINDOWS_PLATFORM
#ifndef CARDS_GAMEWIN_H
#define CARDS_GAMEWIN_H
#include "../Output.h"

class WindowsOutput final : public Output {
public:
    explicit WindowsOutput(bool running);
    WindowsOutput(const WindowsOutput&) = delete;
    WindowsOutput(WindowsOutput&&) = delete;
    WindowsOutput& operator=(const WindowsOutput&) = delete;
    WindowsOutput& operator=(WindowsOutput&&) = delete;
    ~WindowsOutput() final;

    // Singleton pattern implementation
    static WindowsOutput* getInstance(bool running) {
        static WindowsOutput instance(running);
        return &instance;
    }

    void Setup() override;      // Setup operations for the output
    void Update() override;     // Update the console buffer
    void BeginDraw() override;  // Clear the screen
    void Draw() override;       // Draw the console buffer
    void EndDraw() override;    // Display the console buffer on the screen
    void Cleanup() override;    // Cleanup operations for the output

};

#endif //CARDS_GAMEWIN_H
#endif //WINDOWS_PLATFORM
