#include <fstream>
#include <sstream>
#include "CommandDictionary.h"

CommandDictionary::CommandDictionary()
{
	// read commands from file
	std::ifstream file;
	file.open("commands.cfg");
	if (file.is_open())
	{
		std::string readLine;
		while (std::getline(file, readLine))
		{
			// ignore lines that begin with #
			if (readLine[0] != '#')
			{
				std::istringstream iss(readLine);
				int value;
				std::string name, description;

				// Read the integer 'value' and the 'name' first.
				if (iss >> value >> name)
				{
					// Now, capture the entire remainder of the line as 'description'.
					std::getline(iss >> std::ws, description);

					Command command(static_cast<Command::Value>(value));
					command.m_name = name;
					command.m_description = description;

					this->AddCommand(command);
				}
			}
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

void CommandDictionary::AddCommand(const Command& command)
{
	this->m_commandDictionary[command.m_value] = command;
	this->m_commandNameDictionary[command.m_name] = command.m_value;
}

void CommandDictionary::RemoveCommand(const Command& command)
{
	this->m_commandDictionary.erase(command.m_value);
	this->m_commandNameDictionary.erase(command.m_name);
}

bool CommandDictionary::TriggerCommand(Command::Value command)
{
	const auto it = this->m_commandDictionary.find(command);
	if (it != this->m_commandDictionary.end())
	{
		it->second.m_triggered = true;
		return true;
	}
	return false;
}

bool CommandDictionary::UntriggerCommand(Command::Value command)
{
	const auto it = this->m_commandDictionary.find(command);
	if (it != this->m_commandDictionary.end())
	{
		it->second.m_triggered = false;
		return true;
	}
	return false;
}

Command& CommandDictionary::FindCommand(Command::Value value)
{
	return this->m_commandDictionary[value];
}

Command& CommandDictionary::FindCommandByName(const std::string& name)
{
	const auto it = this->m_commandNameDictionary.find(name);
	if (it != this->m_commandNameDictionary.end())
	{
		return this->m_commandDictionary.at(it->second);
	}
	else
	{
		return this->m_commandDictionary.at(Command::Value::INVALID_COMMAND);
	}
}

bool CommandDictionary::HasCommand(const Command::Value value) const
{
	return this->m_commandDictionary.find(value) != this->m_commandDictionary.end();
}
