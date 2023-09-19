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
	std::cout << "Starting Main Menu state..." << std::endl;
}

void MainMenuState::ProcessInput()
{
	std::cout << "Main menu state process input..." << std::endl;
	// get input command using getline
	std::string input;
	getline(std::cin, input);

	// show inputted command to screen with a message
	std::cout << "You entered: " << input << std::endl;

	InputManager::GetInstance()->HandleInput(input);
}

void MainMenuState::Update()
{
	std::cout << "Main menu state update..." << std::endl;

	auto command = InputManager::GetInstance()->GetCommands()->FindCommandByStatus(true);

	switch (command)
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

	InputManager::GetInstance()->Update();
}

void MainMenuState::Draw()
{
	std::cout << "Main menu state drawing to screen..." << std::endl;
	// sleep for 1 second
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
