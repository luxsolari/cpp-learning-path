#pragma once
#ifndef COMMAND_DICTIONARY
#define COMMAND_DICTIONARY
#include <string>
#include <unordered_map>
#include <iostream>

class Command
{
public:
	enum Value : int
	{
		UNINITIALIZED = -999,
		NOT_FOUND = -2,
		INVALID_COMMAND = -1,
		// MAIN MENU CODES
		MAIN_MENU_HELP = 0,
		MAIN_MENU_OPTIONS = 1,
		MAIN_MENU_CREDITS = 2,
		MAIN_MENU_EXIT = 3,
		// OPTIONS MENU COMMANDS
		OPTIONS_MENU_CONTROLS = 4,
		OPTIONS_MENU_EXIT = 5,
		// CONTROLS MENU COMMANDS
		CONTROLS_MENU_EXIT = 6,
	};

	// constructors
	Command() : m_value(Value::INVALID_COMMAND) {}
	Command(const Value value) : m_value(value) {}
	Command(std::string name) : m_value(Command::Value::UNINITIALIZED), m_name(std::move(name)), m_description("/_uninit") {}

	// conversion operators
	constexpr operator Value() const { return m_value; }
	explicit operator bool() const = delete;

	// comparison operators
	bool operator==(const Command& a) const { return m_value == a.m_value; }
	bool operator!=(const Command& a) const { return m_value != a.m_value; }
	bool operator<(const Command& a)  const { return m_value < a.m_value; }
	bool operator>(const Command& a)  const { return m_value > a.m_value; }
	bool operator<=(const Command& a) const { return m_value <= a.m_value; }
	bool operator>=(const Command& a) const { return m_value >= a.m_value; }

	Value m_value;
	std::string m_name;
	std::string m_description;
	bool m_triggered = false;
};

class CommandDictionary
{
public:
	CommandDictionary();
	virtual ~CommandDictionary();
	// singleton
	static CommandDictionary* GetInstance();

	void AddCommand(const Command& command);
	void RemoveCommand(const Command& command);
	bool TriggerCommand(Command::Value command);
	bool UntriggerCommand(Command::Value command);
	Command& FindCommand(Command::Value value);
	Command::Value FindCommandByName(const std::string& name);
	bool HasCommand(Command::Value value) const;

	// getter, return a reference to the dictionary, not a copy
	std::unordered_map<Command::Value, Command>& GetCommandDictionary() { return m_commandDictionary; }
	std::unordered_map<std::string, Command>& GetCommandNameDictionary() { return m_commandNameDictionary; }

private:
	std::unordered_map<Command::Value, Command> m_commandDictionary;
	std::unordered_map<std::string, Command> m_commandNameDictionary; // reverse mapping
};

#endif // COMMAND_DICTIONARY
