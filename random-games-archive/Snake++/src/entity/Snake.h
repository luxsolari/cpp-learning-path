#pragma once
#include <SFML/Graphics.hpp>

struct SnakeSegment {
	SnakeSegment(int x, int y) : position(x, y) {}
	sf::Vector2i position;
};

using SnakeContainer = std::vector<SnakeSegment>;

enum class Direction { None, Up, Down, Left, Right };

class Snake
{
public:
	Snake(int l_blockSize, class TextBox* l_textBox);
	~Snake();

	void setDirection(Direction l_dir);
	Direction getDirection();
	Direction getPhysicalDirection();
	int getSpeed();
	sf::Vector2i getPosition();
	int getLives();
	int getScore();
	void increaseScore();
	bool hasLost();

	void lose();
	void toggleLost();

	void extend();
	void reset();

	void move();
	void tick();
	void cut(int l_segments);
	void render(sf::RenderWindow& l_window);

private:

	void checkCollision();

	SnakeContainer m_snakeBody; // snake body vector.
	int m_size;
	Direction m_dir;
	int m_speed;
	int m_lives;
	int m_score;
	bool m_lost;
	sf::RectangleShape m_bodyRect; // shape used in rendering.

	class TextBox* m_textBox;
};

