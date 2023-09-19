#include <fstream>
#include <sstream>
#include "CommandDictionary.h"

#include <algorithm>
#include <map>

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
				int code = 0;
				int type = 0;
				std::string name, description;

				// Read the integer 'value' and the 'name' first.
				if (iss >> code >> type >> name)
				{
					// Now, capture the entire remainder of the line as 'description'.
					std::getline(iss >> std::ws, description);

					Command command;
					command.m_command_code = static_cast<Command::Code>(code);
					command.m_command_type = static_cast<Command::Type>(type);
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
	this->m_commandDictionary[command.m_command_code] = command;
}

void CommandDictionary::RemoveCommand(const Command& command)
{
	this->m_commandDictionary.erase(command.m_command_code);
}

bool CommandDictionary::TriggerCommand(Command::Code command)
{
	const auto it = this->m_commandDictionary.find(command);
	if (it != this->m_commandDictionary.end())
	{
		it->second.m_triggered = true;
		return true;
	}
	return false;
}

bool CommandDictionary::UntriggerCommand(Command::Code command)
{
	const auto it = this->m_commandDictionary.find(command);
	if (it != this->m_commandDictionary.end())
	{
		it->second.m_triggered = false;
		return true;
	}
	return false;
}

Command& CommandDictionary::FindCommand(Command::Code value)
{
	return this->m_commandDictionary[value];
}

Command& CommandDictionary::FindCommandByName(const std::string& name, const Command::Type type)
{

	// filter dictionary by type with a lambda expression and search for name
	auto it = std::find_if(this->m_commandDictionary.begin(), this->m_commandDictionary.end(),
	[name, type](const std::pair<Command::Code, Command>& command)
	{
		// if name and type match, return true. If general command, return true
		return command.second.m_name == name && (command.second.m_command_type == type || command.second.m_command_type == Command::Type::GENERAL);
	});

	// if found return the command
	if (it != this->m_commandDictionary.end())
	{
		return it->second;
	}
	// else return the invalid command
	return this->m_commandDictionary[Command::Code::INVALID_COMMAND];
}

bool CommandDictionary::HasCommand(const Command::Code value) const
{
	return this->m_commandDictionary.find(value) != this->m_commandDictionary.end();
}
