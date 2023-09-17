#pragma once
#include "LoopState.h"
class OptionsMenuState :
    public LoopState
{
public:
	OptionsMenuState();
	virtual ~OptionsMenuState() override;

	virtual void Start() override;
	virtual void ProcessInput() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Finish() override;

private:
	class InputManager* m_inputManager;

};

