#pragma once
#include "LoopState.h"

class MainMenuState :
    public LoopState
{
public:
	MainMenuState();
	~MainMenuState();

	virtual void Start() override;
	virtual void ProcessInput() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Finish() override;

};

