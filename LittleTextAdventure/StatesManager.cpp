#include "StatesManager.h"
#include "MainMenuState.h"

StatesManager::StatesManager() : m_currentState(nullptr)
{
	this->m_states.push_back(new MainMenuState());
	this->m_currentState = this->m_states.front();
}

StatesManager::~StatesManager()
{
}

StatesManager* StatesManager::GetInstance()
{
	static StatesManager instance;
	return &instance;
}

void StatesManager::AddState(LoopState* state)
{
	this->m_states.push_back(state);
}

void StatesManager::RemoveState(LoopState* state)
{
	this->m_states.remove(state);
}

void StatesManager::ChangeState(LoopState* state)
{
	this->m_currentState = state;
}

LoopState* StatesManager::GetCurrentState()
{
	return this->m_currentState;
}

void StatesManager::Update()
{
	while (this->m_currentState != nullptr)
	{
		if (!this->m_currentState->IsRunning())
		{
			this->RemoveState(this->m_currentState);
			this->m_currentState = nullptr;

			if (!this->m_states.empty())
			{
				this->m_currentState = this->m_states.front();
				this->m_currentState->Start();
			}
		}
		else
		{
			this->m_currentState->Play();
		}
	}
}
