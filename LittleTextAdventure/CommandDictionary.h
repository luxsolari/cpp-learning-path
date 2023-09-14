#pragma once
#include <string>
#include <map>
#include <iostream>

class CommandDictionary
{
public:
	CommandDictionary();
	~CommandDictionary();
	// singleton
	static CommandDictionary* GetInstance();

	void AddCommand(std::string command, std::string description);
	void PrintCommands();
	void PrintCommand(std::string command);
	void PrintCommandDescription(std::string command);

private:
	std::map<std::string, std::string> m_commandDictionary;
};

