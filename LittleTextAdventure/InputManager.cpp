#include "InputManager.h"
#include "CommandDictionary.h"

InputManager::InputManager() : commands(*CommandDictionary::GetInstance())
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

CommandDictionary* InputManager::GetCommands()
{
	return this->commands.GetInstance();
}

void InputManager::HandleInput()
{
	// TODO: implement this function
	// check command against dictionary
	// if command is found, mark as "triggered"
	// if command is not found, mark INVALID_COMMAND as "triggered"

}

void InputManager::Update()
{
	// TODO:
	// Check for "triggered" commands
	// If found, execute, unmark "triggered" from executed command afterwards
	// If INVALID_COMMAND is "triggered", print error message, unmark "triggered" from INVALID_COMMAND afterwards
	// If no commands are "triggered", do nothing.

}
