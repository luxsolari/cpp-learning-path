#include "Game.h"
#include "../ui/TextBox.h"

Game::Game() : 
	m_window("C++ Snake", sf::Vector2u(1280, 720)), 
	m_snake(this->m_world.getBlockSize(), &(this->m_textBox)),
	m_world(sf::Vector2u(1280, 720))
{
	this->m_clock.restart();
	this->m_textBox.setup(5, 14, 350, sf::Vector2f(225, 0));

	srand(time(nullptr));
	this->m_textBox.add("Seeded random number generator with: " + std::to_string(time(NULL)));
}

Game::~Game()
{
}

void Game::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		&& m_snake.getPhysicalDirection() != Direction::Down)
	{
		m_snake.setDirection(Direction::Up);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
		&& m_snake.getPhysicalDirection() != Direction::Up)
	{
		m_snake.setDirection(Direction::Down);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		&& m_snake.getPhysicalDirection() != Direction::Right)
	{
		m_snake.setDirection(Direction::Left);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
		&& m_snake.getPhysicalDirection() != Direction::Left)
	{
		m_snake.setDirection(Direction::Right);
	}
}

void Game::update()
{
	this->m_window.update();
	float timestep = 1.0f / m_snake.getSpeed();

	if (this->m_elapsed >= sf::seconds(timestep))
	{
		this->m_snake.tick();
		this->m_world.update(this->m_snake);
		this->m_elapsed -= sf::seconds(timestep);

		if (this->m_snake.hasLost())
		{
			this->m_snake.reset();
		}
	}
}

void Game::render()
{
	this->m_window.beginDraw();
	this->m_world.render(m_window.getRenderWindow());
	this->m_snake.render(m_window.getRenderWindow());
	this->m_textBox.render(m_window.getRenderWindow());
	this->m_window.endDraw();
}

Window* Game::getWindow()
{
	return &(this->m_window);
}

sf::Time Game::getElapsed()
{
	return this->m_elapsed;
}

void Game::restartClock()
{
	this->m_elapsed += this->m_clock.restart();
}
