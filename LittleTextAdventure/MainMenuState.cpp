#include <iostream>
#include <string>
#include "CommandDictionary.h"
#include "InputManager.h"
#include "MainMenuState.h"

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
	std::cin.get();

}

void MainMenuState::Update()
{
	std::cout << "Main menu state update..." << std::endl;
}

void MainMenuState::Draw()
{
	std::cout << "Main menu state drawing to screen..." << std::endl;

	// clear screen
	
}

void MainMenuState::Finish()
{
	std::cout << "Finishing Main menu state... " << std::endl;
}
