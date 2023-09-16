#pragma once

class CommandDictionary;

class InputManager
{
public:
	InputManager();
	~InputManager();

	// singleton
	static InputManager* GetInstance();

	CommandDictionary& GetCommands();
	void HandleInput();
	void Update();

private:
	CommandDictionary& commands;

};
