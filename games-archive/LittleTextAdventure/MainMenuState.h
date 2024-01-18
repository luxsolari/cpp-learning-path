#pragma once
#include "LoopState.h"

class MainMenuState :
    public LoopState
{
public:
	MainMenuState();
	virtual ~MainMenuState() override;

	virtual void Start() override;
	virtual void ProcessInput() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Finish() override;

private:
	class Command* m_triggeredCommand = nullptr;
	class InputManager* m_inputManager;
};

