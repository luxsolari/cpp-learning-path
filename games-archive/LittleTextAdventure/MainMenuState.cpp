#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "MainMenuState.h"
#include "OptionsMenuState.h"
#include "CommandDictionary.h"
#include "StatesManager.h"

MainMenuState::MainMenuState() : m_inputManager(InputManager::GetInstance())
{
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::Start()
{
	if (this->m_currentStatus == Status::NOT_STARTED)
	{
		std::cout << "Starting Main Menu state..." << std::endl;
		this->m_currentStatus = Status::RUNNING;
		this->m_isRunning = true;
	}
	else if (this->m_currentStatus == Status::PAUSED)
	{
		std::cout << "Resuming Main Menu state..." << std::endl;
		this->m_currentStatus = Status::RUNNING;
		this->m_isRunning = true;
	}
}

void MainMenuState::ProcessInput()
{
	std::cout << "Main menu state process input..." << std::endl;
	///e get input command using getline
	std::string input;
	getline(std::cin, input);
	InputManager::GetInstance()->HandleInput(input, Command::Type::MAIN_MENU);
}

void MainMenuState::Update()
{
	std::cout << "Main menu state update..." << std::endl;
	this->m_triggeredCommand = &(InputManager::GetInstance()->GetCommands()->FindCommandByStatus(true));
	InputManager::GetInstance()->Update();
	
	switch (this->m_triggeredCommand->m_command_code)
	{
	case Command::Code::MAIN_MENU_OPTIONS:
		StatesManager::GetInstance()->ChangeState(new OptionsMenuState());
		break;
	case Command::Code::MAIN_MENU_EXIT:
		this->Stop();
		break;
	default:
		break;
	}
}

void MainMenuState::Draw()
{
	std::cout << "Main menu state drawing to screen..." << std::endl;

	switch (this->m_triggeredCommand->m_command_code)
	{
	case Command::Code::MAIN_MENU_OPTIONS:
		std::cout << "Transitioning to options menu..." << std::endl;
		break;
	case Command::Code::MAIN_MENU_EXIT:
		std::cout << "Exiting game..." << std::endl;
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

void MainMenuState::Finish()
{
	std::cout << "Finishing Main menu state... " << std::endl;
}
