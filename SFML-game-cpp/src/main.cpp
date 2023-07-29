#include "managers/StateManager.h"
#include "Game.h"

int main()
{
	Game game;
	sf::Clock clock;
	sf::Time elapsed = clock.restart();

	while (!game.GetWindow()->IsDone())
	{
		game.Update();
		game.Render();
		game.LateUpdate();
	}

	return 0;
}
