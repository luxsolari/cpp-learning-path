#include <thread>
#include <chrono>
#include "LoopState.h"

LoopState::LoopState() : m_isRunning(true)
{
}

LoopState::~LoopState()
{
}

void LoopState::Play()
{
	this->Start();
	while (this->IsRunning())
	{
		this->ProcessInput();
		this->Update();
		this->Draw();
		// sleep for 1 second
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void LoopState::Stop()
{
	this->m_isRunning = false;
}

bool LoopState::IsRunning() const
{
	return this->m_isRunning;
}
