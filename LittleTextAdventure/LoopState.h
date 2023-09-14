#pragma once

class LoopState
{
public:
	LoopState();
	~LoopState();

	virtual void Start() = 0;
	virtual void ProcessInput() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Finish() = 0;

	virtual void Play();
	virtual void Stop();

protected:
	bool m_isRunning;

public:
	bool IsRunning() const;
};

