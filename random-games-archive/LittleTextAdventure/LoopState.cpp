#include <thread>
#include <chrono>
#include "LoopState.h"
#include <iostream>

LoopState::LoopState() : m_isRunning(true)
{
}

LoopState::~LoopState() = default;

void LoopState::Play()
{
	this->Start();
	while (this->IsRunning())
	{
		this->ProcessInput();
		this->Update();
		this->Draw();
	}
}

void LoopState::Stop()
{
	if (!this->m_isRunning)
	{
		std::cerr << "Cannot stop a state that is not running!" << std::endl;
		return;
	}
	this->m_currentStatus = Status::PAUSED;
	this->m_isRunning = false;
	this->Finish();
}

bool LoopState::IsRunning() const
{
	return this->m_isRunning;
}

Status LoopState::GetCurrentStatus() const
{
	return this->m_currentStatus;
}
