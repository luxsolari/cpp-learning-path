#include <iostream>
#include <string>
#include "MainMenuState.h"

MainMenuState::MainMenuState()
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
	// check if input is "exit"
	if (input == "exit")
	{
		this->Stop();
	}

}

void MainMenuState::Update()
{
	std::cout << "Main menu state update..." << std::endl;
}

void MainMenuState::Draw()
{
	std::cout << "Main menu state drawing to screen..." << std::endl;
}

void MainMenuState::Finish()
{
	std::cout << "Finishing Main menu state... " << std::endl;
}
