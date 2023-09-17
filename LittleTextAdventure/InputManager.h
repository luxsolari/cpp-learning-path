#pragma once
#include <string>

class CommandDictionary;

class InputManager
{
public:
	InputManager();
	virtual ~InputManager();

	// singleton
	static InputManager* GetInstance();

	CommandDictionary* GetCommands() const;
	void HandleInput(const std::string& input);
	void Update();

private:
	CommandDictionary* commands;

};
