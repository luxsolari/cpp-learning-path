#pragma once
#include <list>
#include "LoopState.h"

class StatesManager
{
public:
	StatesManager();
	~StatesManager();
	// singleton
	static StatesManager* GetInstance();

	void AddState(LoopState* state);
	void RemoveState(LoopState* state);
	void ChangeState(LoopState* state);
	LoopState* GetCurrentState();
	void Update();

private:
	LoopState* m_currentState;
	std::list<LoopState*> m_states;	
};

