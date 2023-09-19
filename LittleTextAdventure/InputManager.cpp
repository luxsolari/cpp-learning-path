#include "InputManager.h"
#include "CommandDictionary.h"

InputManager::InputManager() : commands(CommandDictionary::GetInstance()){}
InputManager::~InputManager() = default;

InputManager* InputManager::GetInstance()
{
	static InputManager instance;
	return &instance;
}

CommandDictionary* InputManager::GetCommands() const
{
	return this->commands;
}

void InputManager::HandleInput(const std::string& input) const
{
	this->commands->TriggerCommand(this->commands->FindCommandByName(input, Command::Type::MAIN_MENU).m_command_code);
}

void InputManager::Update() const
{
	// Check for "triggered" commands
	// If found, unmark "triggered" from executed command afterwards
	// If INVALID_COMMAND is "triggered", print error message, unmark "triggered" from INVALID_COMMAND afterwards
	// If no commands are "triggered", do nothing.
	if (this->commands->FindCommand(Command::Code::INVALID_COMMAND).m_triggered)
	{
		std::cout << "Invalid command!" << std::endl;
		this->commands->UntriggerCommand(Command::Code::INVALID_COMMAND);
	}
	else
	{
		for (auto it = this->GetCommands()->GetCommandDictionary().begin(); it != this->GetCommands()->GetCommandDictionary().end(); ++it)
		{
			if (it->second.m_triggered)
			{
				std::cout << "Command triggered: " << it->second.m_name << std::endl;
				it->second.m_triggered = false;
				this->commands->UntriggerCommand(it->second.m_command_code);
			}
		}
	}
}
