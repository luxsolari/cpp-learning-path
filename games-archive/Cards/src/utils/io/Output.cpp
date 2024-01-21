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
    m_outputThread = std::thread(&Output::OutputThreadFunction, this);
}

void Output::Stop()
{
    m_isRunning = false;
    if (m_outputThread.joinable()) {
        m_outputThread.join();
    }
}

void Output::OutputThreadFunction()
{
    while (m_isRunning) {
        Update();
        BeginDraw();
        Draw();
        EndDraw();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));  // Adjust as needed
    }
}

