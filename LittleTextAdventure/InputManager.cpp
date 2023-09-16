#include "InputManager.h"
#include "CommandDictionary.h"

InputManager::InputManager() : commands(CommandDictionary::GetInstance())
{
}

InputManager::~InputManager()
{
}

InputManager* InputManager::GetInstance()
{
	static InputManager instance;
	return &instance;
}

CommandDictionary& InputManager::GetCommands()
{
	return this->commands.GetInstance();
}

void InputManager::HandleInput()
{
	// check command against dictionary
	// if command is found, execute command
	// if command is not found, print error message

}

void InputManager::Update()
{
	std::string input;
	std::cout << "Enter a command: ";
	std::cin >> input;
}
