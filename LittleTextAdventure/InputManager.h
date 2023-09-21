#pragma once
#include <string>

#include "CommandDictionary.h"

class CommandDictionary;

class InputManager
{
public:
	InputManager();
	virtual ~InputManager();

	// singleton
	static InputManager* GetInstance();

	CommandDictionary* GetCommands() const;
	void HandleInput(const std::string& input, const Command::Type type) const;
	void Update() const;

private:
	CommandDictionary* commands;

};
