//
// Created by luxsolari on 1/15/2024.
//
#include "Output.h"

Output::Output(bool running) : m_isRunning(running)
{

}

Output::~Output()
{

}

void Output::Start()
{
    this->m_isRunning = true;
}

void Output::Stop()
{
    m_isRunning = false;

    if (m_outputThread.joinable()) {
        m_outputThread.join();
    }

    // Cleanup resources used after the output thread has stopped. This should be called last.
    this->Cleanup();
}

void Output::OutputThreadFunction()
{
    while (m_isRunning) {
        std::this_thread::sleep_for(std::chrono::seconds (1/120));  // Adjust as needed
        Update();
        std::this_thread::sleep_for(std::chrono::seconds(1/60));  // Adjust as needed
        BeginDraw();
        Draw();
        EndDraw();
    }
}

