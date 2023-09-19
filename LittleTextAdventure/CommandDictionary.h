#pragma once
#ifndef COMMAND_DICTIONARY
#define COMMAND_DICTIONARY
#include <string>
#include <unordered_map>
#include <iostream>

class Command
{
public:
	enum class Code : int
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

	enum class Type
	{
		UNINITIALIZED = -999,
		ERROR = -1,
		GENERAL = 0,
		MAIN_MENU = 1,
		OPTIONS_MENU = 2,
		CONTROLS_MENU = 3
	};

	// constructors
	Command() : m_command_code(Code::INVALID_COMMAND) {}
	Command(const Code value) : m_command_code(value) {}
	Command(std::string name) : m_command_code(Command::Code::UNINITIALIZED), m_name(std::move(name)), m_description("/_uninit") {}

	// conversion operators
	constexpr operator Code() const { return m_command_code; }
	explicit operator bool() const = delete;

	// comparison operators
	bool operator==(const Command& a) const { return m_command_code == a.m_command_code; }
	bool operator!=(const Command& a) const { return m_command_code != a.m_command_code; }
	bool operator<(const Command& a)  const { return m_command_code < a.m_command_code; }
	bool operator>(const Command& a)  const { return m_command_code > a.m_command_code; }
	bool operator<=(const Command& a) const { return m_command_code <= a.m_command_code; }
	bool operator>=(const Command& a) const { return m_command_code >= a.m_command_code; }

	// stream operators
	friend std::ostream& operator<<(std::ostream& os, const Command::Code command)
	{
		os << static_cast<int>(command);
		return os;
	}

	friend std::ostream& operator<<(std::ostream& os, const Command::Type type)
	{
		os << static_cast<int>(type);
		return os;
	}

	friend std::istream& operator>>(std::istream& is, Command::Code command)
	{
		int value;
		is >> value;
		command = static_cast<Command::Code>(value);
		return is;
	}

	friend std::istream& operator>>(std::istream& is, Command::Type type)
	{
		int value;
		is >> value;
		type = static_cast<Command::Type>(value);
		return is;
	}
	
	Code m_command_code = Code::UNINITIALIZED;
	Type m_command_type = Type::UNINITIALIZED;
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
	bool TriggerCommand(Command::Code command);
	bool UntriggerCommand(Command::Code command);
	Command& FindCommand(Command::Code value);
	Command& FindCommandByName(const std::string& name, const Command::Type type);
	bool HasCommand(Command::Code value) const;

	// getter, return a reference to the dictionary, not a copy
	std::unordered_map<Command::Code, Command>& GetCommandDictionary() { return m_commandDictionary; }

private:
	std::unordered_map<Command::Code, Command> m_commandDictionary;
};

#endif // COMMAND_DICTIONARY
