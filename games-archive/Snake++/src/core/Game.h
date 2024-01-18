#pragma once
#include "Window.h"
#include "../entity/World.h"
#include "../entity/Snake.h"
#include "../ui/TextBox.h"

class Game
{
public:
	Game();
	~Game();

	void handleInput();
	void update();
	void render();
	Window* getWindow();
	sf::Time getElapsed();
	void restartClock();

private:
	Window m_window;
	TextBox m_textBox;

	sf::Clock m_clock;
	sf::Time m_elapsed;

	World m_world;
	Snake m_snake;
};

