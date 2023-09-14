#include "CommandDictionary.h"

CommandDictionary::CommandDictionary()
{
	this->AddCommand("exit", "Exit the game");
}

CommandDictionary::~CommandDictionary()
{
}

CommandDictionary* CommandDictionary::GetInstance()
{
	static CommandDictionary instance;
	return &instance;
}

void CommandDictionary::AddCommand(std::string command, std::string description)
{
	this->m_commandDictionary[command] = description;
}
