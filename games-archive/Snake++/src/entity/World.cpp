#include "World.h"

World::World(sf::Vector2u l_windowSize)
{
	this->m_blockSize = 24;
	this->m_windowSize = l_windowSize;
	this->respawnApple();
	this->m_appleShape.setFillColor(sf::Color::Red);
	this->m_appleShape.setRadius(this->m_blockSize / 2);

	for (int i = 0; i < 4; ++i)
	{
		this->m_bounds[i].setFillColor(sf::Color(150, 0, 0));
		if (!((i + 1) % 2)) {
			this->m_bounds[i].setSize(sf::Vector2f(this->m_windowSize.x,
				this->m_blockSize));
		}
		else {
			this->m_bounds[i].setSize(sf::Vector2f(this->m_blockSize,
				this->m_windowSize.y));
		}
		if (i < 2) {
			this->m_bounds[i].setPosition(0, 0);
		}
		else {
			this->m_bounds[i].setOrigin(this->m_bounds[i].getSize());
			this->m_bounds[i].setPosition(sf::Vector2f(this->m_windowSize));
		}
	}

}

World::~World()
{
}

int World::getBlockSize()
{
	return this->m_blockSize;
}

void World::respawnApple()
{
	int maxX = (this->m_windowSize.x / this->m_blockSize) - 2;
	int maxY = (this->m_windowSize.y / this->m_blockSize) - 2;
	this->m_item = sf::Vector2i(rand() % maxX + 1, rand() % maxY + 1);
	this->m_appleShape.setPosition(this->m_item.x * this->m_blockSize,
		this->m_item.y * this->m_blockSize);
}

void World::update(Snake& l_player)
{
	if (l_player.getPosition() == this->m_item) {
		l_player.extend();
		l_player.increaseScore();
		this->respawnApple();
	}
	int gridSize_x = this->m_windowSize.x / this->m_blockSize;
	int gridSize_y = this->m_windowSize.y / this->m_blockSize;
	if (l_player.getPosition().x <= 0 ||
		l_player.getPosition().y <= 0 ||
		l_player.getPosition().x >= gridSize_x - 1 ||
		l_player.getPosition().y >= gridSize_y - 1) {
		l_player.lose();
	}

}

void World::render(sf::RenderWindow& l_window)
{
	for (int i = 0; i < 4; ++i) {
		l_window.draw(this->m_bounds[i]);
	}
	l_window.draw(this->m_appleShape);
}
