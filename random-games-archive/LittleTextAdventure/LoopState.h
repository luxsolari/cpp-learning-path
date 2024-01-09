#pragma once
#include "Status.h"

class LoopState
{
public:
	LoopState();
	virtual ~LoopState();

	virtual void Start() = 0;
	virtual void ProcessInput() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Finish() = 0;

	virtual void Play();
	virtual void Stop();

protected:
	bool m_isRunning;
	Status m_currentStatus = Status::NOT_STARTED;
public:
	bool IsRunning() const;
	void SetIsRunning(bool isRunning);
	
	Status GetCurrentStatus() const;
};

