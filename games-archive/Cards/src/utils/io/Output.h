//
// Created by luxsolari on 12/01/2024.
//

#ifndef CARDS_CONSOLE_H
#define CARDS_CONSOLE_H
#include <thread>
#include <mutex>

class Output {
public:
    explicit Output(bool running);
    Output(const Output&) = delete;
    Output(Output&&) = delete;
    Output& operator=(const Output&) = delete;
    Output& operator=(Output&&) = delete;
    virtual ~Output();

    virtual void Setup() = 0; // Setup the console previously to start using it (e.g. set the console size).
    void Start(); // Start the output thread. This will set the input thread object to run.
    void Stop();  // Stop the output thread. This will stop the input thread object from running.
    virtual void Cleanup() = 0; // Cleanup resources used after the output thread has stopped.

    void OutputThreadFunction();

    virtual void Update() = 0;
    virtual void BeginDraw() = 0;
    virtual void Draw() = 0;
    virtual void EndDraw() = 0;

protected:
    bool m_isRunning;
    std::thread m_outputThread;
    std::thread m_resizeThread;
    mutable std::mutex m_outputMutex;

    // console dimensions
    int m_width;
    int m_height;

    void LockOutput() const {
        m_outputMutex.lock();
    }

    void UnlockOutput() const {
        m_outputMutex.unlock();
    }
};

#endif //CARDS_CONSOLE_H
