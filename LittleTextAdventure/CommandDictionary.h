#pragma once
#ifndef _COMMAND_DICTIONARY
#define _COMMAND_DICTIONARY
#include <string>
#include <unordered_map>
#include <iostream>

class Command
{
public:
	enum Value : size_t
	{
		UNINITIALIZED = -999,
		NOT_FOUND = -2,
		INVALID_COMMAND = -1,
		// MAIN MENU CODES
		MAIN_MENU_HELP = 0,
		MAIN_MENU_OPTIONS = 1,
		MAIN_MENU_EXIT = 2,
		// OPTIONS MENU COMMANDS
		OPTIONS_MENU_CONTROLS = 3,
		OPTIONS_MENU_EXIT = 4,
		// CONTROLS MENU COMMANDS
		CONTROLS_MENU_EXIT = 5,
	};

	// constructors
	Command() : m_value(Value::INVALID_COMMAND) {}
	Command(Value value) : m_value(value) {}
	Command(const std::string& name) : m_name(name), m_description("/_uninit"), m_value(Command::Value::UNINITIALIZED) {}

	// conversion operators
	constexpr operator Value() const { return m_value; }
	explicit operator bool() const = delete;

	// comparison operators
	bool operator==(Command a) const { return m_value == a.m_value; }
	bool operator!=(Command a) const { return m_value != a.m_value; }
	bool operator<(Command a)  const { return m_value < a.m_value; }
	bool operator>(Command a)  const { return m_value > a.m_value; }
	bool operator<=(Command a) const { return m_value <= a.m_value; }
	bool operator>=(Command a) const { return m_value >= a.m_value; }

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
	static CommandDictionary* GetInstance()
	{
		static CommandDictionary instance;
		return &instance;
	}

	void AddCommand(const Command& command);
	void RemoveCommand(Command command);
	Command FindCommand(Command::Value value);
	Command FindCommandByName(const std::string& name) const;
	bool HasCommand(Command::Value value);


private:
	std::unordered_map<Command::Value, Command> m_commandDictionary;
	std::unordered_map<std::string, Command::Value> m_commandNameDictionary; // reverse mapping
};

#endif // _COMMAND_DICTIONARY
