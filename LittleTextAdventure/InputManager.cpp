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

void InputManager::HandleInput()
{

}

void InputManager::Update()
{

}
