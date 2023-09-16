#pragma once

class CommandDictionary;

class InputManager
{
public:
	InputManager();
	~InputManager();

	// singleton
	static InputManager* GetInstance();
	
	void HandleInput();
	void Update();
	void Reset();

private:
	CommandDictionary* commands;

};
