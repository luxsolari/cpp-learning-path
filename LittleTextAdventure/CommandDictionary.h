#pragma once
#ifndef _COMMAND_DICTIONARY
#include <string>
#include <unordered_map>
#include <iostream>

class Command
{
public:
	enum Value : size_t
	{
		INVALID_COMMAND   = -1,
		MAIN_MENU_HELP    = 0,
		MAIN_MENU_OPTIONS = 1,
		MAIN_MENU_EXIT    = 2
	};

	// constructors
	Command() : m_value(Value::INVALID_COMMAND) {};
	Command(Value value) : m_value(value) {}

	// conversion operators
	constexpr operator Value() const { return m_value; }
	explicit operator bool() const = delete;

	// comparison operators
	bool operator==(Command a) const { return m_value == a.m_value; }
	bool operator!=(Command a) const { return m_value != a.m_value; }

	Value m_value;
	std::string m_name;
	std::string m_description;
};

class CommandDictionary
{
public:
	CommandDictionary();
	~CommandDictionary();
	// singleton
	static CommandDictionary& GetInstance()
	{
		static CommandDictionary instance;
		return instance;
	}

	void AddCommand(const Command& command);
	void RemoveCommand(Command command);
	Command FindCommand(Command::Value value);
	Command FindCommandByName(std::string& name) const;
	bool HasCommand(Command::Value value);


private:
	std::unordered_map<Command::Value, Command> m_commandDictionary;
	std::unordered_map<std::string, Command::Value> m_commandNameDictionary; // reverse mapping
};

#endif // _COMMAND_DICTIONARY
