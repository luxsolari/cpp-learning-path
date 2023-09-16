#include <istream>
#include <fstream>
#include "CommandDictionary.h"

CommandDictionary::CommandDictionary()
{
	// read commands from file
	std::ifstream file;
	file.open("commands.cfg");
	if (file.is_open())
	{
		std::string command;
		std::string description;
		// read command key up to first space (command) and then read the rest of the line (description)
		while (file >> command)
		{
			file.ignore(1);
			getline(file, description);
			this->m_commandDictionary[command] = description;
		}
		file.close();
	}
	else
	{
		std::cout << "Unable to open file" << std::endl;
	}

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

void CommandDictionary::PrintCommands()
{
	for (auto& command : this->m_commandDictionary)
	{
		std::cout << command.first << " - " << command.second << std::endl;
	}
}

void CommandDictionary::PrintCommand(std::string command)
{
	if (this->m_commandDictionary.find(command) != this->m_commandDictionary.end())
	{
		std::cout << this->m_commandDictionary[command] << std::endl;
	}
	else
	{
		std::cout << "Command not found" << std::endl;
	}
}

void CommandDictionary::PrintCommandDescription(std::string command)
{
	if (this->m_commandDictionary.find(command) != this->m_commandDictionary.end())
	{
		std::cout << this->m_commandDictionary[command] << std::endl;
	}
	else
	{
		std::cout << "Command not found" << std::endl;
	}
}
