#include <iostream>
#include <string>
#include "MainMenuState.h"
#include "CommandDictionary.h"

MainMenuState::MainMenuState() : commands(CommandDictionary::GetInstance())
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

	// clear screen
	system("cls");

	this->commands->PrintCommands();
}

void MainMenuState::Finish()
{
	std::cout << "Finishing Main menu state... " << std::endl;
}
