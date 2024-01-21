//
// Created by Lux Solari on 12/01/2024.
//
#ifdef UNIX_PLATFORM
#ifndef CARDS_UNIXCONSOLE_H
#define CARDS_UNIXCONSOLE_H
#include "../Output.h"

class UnixOutput final : public Output {
public:
    explicit UnixOutput(bool running);
    UnixOutput(const UnixOutput&) = delete;
    UnixOutput(UnixOutput&&) = delete;
    UnixOutput& operator=(const UnixOutput&) = delete;
    UnixOutput& operator=(UnixOutput&&) = delete;
    ~UnixOutput() final;

    // Singleton
    static UnixOutput* getInstance(bool running) {
        static UnixOutput instance(running);
        return &instance;
    }

    void Setup() override;      // Setup operations for the output
    void Update() override;     // Update the console buffer
    void BeginDraw() override;  // Clear the screen
    void Draw() override;       // Draw the console buffer
    void EndDraw() override;    // Display the console buffer on the screen
    void Cleanup() override;    // Cleanup operations for the output

};

#endif //CARDS_UNIXCONSOLE_H
#endif //UNIX_PLATFORM
