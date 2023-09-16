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

void CommandDictionary::AddCommand(const Command& command)
{
	this->m_commandDictionary[command.m_value] = command;
	this->m_commandNameDictionary[command.m_name] = command;
}

void CommandDictionary::RemoveCommand(Command command)
{
}

Command CommandDictionary::FindCommand(Command::Value value)
{
	return Command();
}

Command CommandDictionary::FindCommandByName(std::string& name) const
{
	auto it = this->m_commandNameDictionary.find(name);
	if (it != this->m_commandNameDictionary.end())
	{
		return it->second;
	}
	else
	{
		return Command(Command::Value::INVALID_COMMAND);
	}
}

bool CommandDictionary::HasCommand(Command::Value value)
{
	return false;
}
