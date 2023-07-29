#ifndef CMAKESFMLPROJECT_GAME_H
#define CMAKESFMLPROJECT_GAME_H
#include "constants/Globals.h"
#include "managers/WindowManager.h"
#include "managers/StateManager.h"

class Game 
{
public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void LateUpdate();
	void Render();
	WindowManager* GetWindow();
	sf::Time GetElapsed();
	void RestartClock();

private:
	WindowManager m_window;
	StateManager m_stateManager;
	SharedContext m_context;

	sf::Clock m_clock;
	sf::Time m_elapsed;

};

#endif // !CMAKESFMLPROJECT_GAME_H
