#include "CommandDictionary.h"
#include "InputManager.h"
#include "OptionsMenuState.h"

#include <chrono>
#include <iostream>
#include <thread>

OptionsMenuState::OptionsMenuState() : m_inputManager(InputManager::GetInstance())
{
}

OptionsMenuState::~OptionsMenuState()
{
}

void OptionsMenuState::Start()
{
    std::cout << "Starting Options Menu state..." << std::endl;
    if (!this->m_isRunning) this->m_isRunning = true;
}

void OptionsMenuState::ProcessInput()
{
    std::cout << "Options menu state process input..." << std::endl;
    // get input command using getline
    std::string input;
    getline(std::cin, input);
    InputManager::GetInstance()->HandleInput(input, Command::Type::OPTIONS_MENU);
}

void OptionsMenuState::Update()
{
    std::cout << "Options menu state update..." << std::endl;
    this->m_triggeredCommand = &(InputManager::GetInstance()->GetCommands()->FindCommandByStatus(true));
    InputManager::GetInstance()->Update();
    
    switch (this->m_triggeredCommand->m_command_code)
    {
    case Command::Code::OPTIONS_MENU_EXIT:
            this->Stop();
            break;
    default:
            break;
    }
}

void OptionsMenuState::Draw()
{
    std::cout << "Options menu state drawing to screen..." << std::endl;

    switch (this->m_triggeredCommand->m_command_code)
    {
    case Command::Code::OPTIONS_MENU_EXIT:
        std::cout << "Transitioning to main menu..." << std::endl;
        break;
    case Command::Code::INVALID_COMMAND:
        std::cout << "Invalid Command!" << std::endl;
        break;
    default:
        break;
    }

    // draw "loading dots"
    std::this_thread::sleep_for(std::chrono::milliseconds(750));
    std::cout << ".";
    std::this_thread::sleep_for(std::chrono::milliseconds(750));
    std::cout << ".";
    std::this_thread::sleep_for(std::chrono::milliseconds(750));
    std::cout << ".";
    std::this_thread::sleep_for(std::chrono::milliseconds(750));
    // clear screen - todo in a portable way and in a thread safe way and not using system()
    system("cls"); // windows only
}

void OptionsMenuState::Finish()
{
    std::cout << "Finishing Options menu state... " << std::endl;
}
