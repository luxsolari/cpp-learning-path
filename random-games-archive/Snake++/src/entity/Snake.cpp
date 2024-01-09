#include "Snake.h"
#include "../ui/TextBox.h"

Snake::Snake(int l_blockSize, TextBox* l_textBox)
{
	this->m_size = l_blockSize;
	this->m_bodyRect.setSize(sf::Vector2f(l_blockSize - 1, l_blockSize - 1));
	this->m_textBox = l_textBox;
	this->reset();
}

Snake::~Snake()
{
}

void Snake::setDirection(Direction l_dir)
{
	this->m_dir = l_dir;
}

Direction Snake::getDirection()
{
	return this->m_dir;
}

Direction Snake::getPhysicalDirection()
{
	if (this->m_snakeBody.size() <= 1) 
	{
		return Direction::None;
	}

	SnakeSegment& head = this->m_snakeBody[0];
	SnakeSegment& neck = this->m_snakeBody[1];

	if (head.position.x == neck.position.x)
	{
		return (head.position.y > neck.position.y) ? Direction::Down : Direction::Up;
	}
	else if (head.position.y == neck.position.y)
	{
		return (head.position.x > neck.position.x) ? Direction::Right : Direction::Left;
	}

	return Direction::None;
}

int Snake::getSpeed()
{
	return this->m_speed;
}

sf::Vector2i Snake::getPosition()
{
	return (!m_snakeBody.empty() ? 
		m_snakeBody.front().position : 
		sf::Vector2i(1, 1));
}

int Snake::getLives()
{
	return this->m_lives;
}

int Snake::getScore()
{
	return this->m_score;
}

void Snake::increaseScore()
{
	this->m_score += 10;
	this->m_textBox->add("You got an apple! Score: " + std::to_string(m_score));
}

bool Snake::hasLost()
{
	return this->m_lost;
}

void Snake::lose()
{
	this->m_lost = true;
}

void Snake::toggleLost()
{
	this->m_lost = !this->m_lost;
}

void Snake::extend()
{
	if (this->m_snakeBody.empty()) { return; }
	SnakeSegment& tail_head = this->m_snakeBody[this->m_snakeBody.size() - 1];

	if (this->m_snakeBody.size() > 1) {
		SnakeSegment& tail_bone = this->m_snakeBody[this->m_snakeBody.size() - 2];
		if (tail_head.position.x == tail_bone.position.x) {
			if (tail_head.position.y > tail_bone.position.y) {
				this->m_snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
			}
			else {
				this->m_snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
			}
		}
		else if (tail_head.position.y == tail_bone.position.y) {
			if (tail_head.position.x > tail_bone.position.x) {
				this->m_snakeBody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
			}
			else {
				this->m_snakeBody.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
			}
		}
	}
	else {
		if (this->m_dir == Direction::Up) {
			this->m_snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y + 1));
		}
		else if (this->m_dir == Direction::Down) {
			this->m_snakeBody.push_back(SnakeSegment(tail_head.position.x, tail_head.position.y - 1));
		}
		else if (this->m_dir == Direction::Left) {
			this->m_snakeBody.push_back(SnakeSegment(tail_head.position.x + 1, tail_head.position.y));
		}
		else if (this->m_dir == Direction::Right) {
			this->m_snakeBody.push_back(SnakeSegment(tail_head.position.x - 1, tail_head.position.y));
		}
	}
}

void Snake::reset()
{
	this->m_snakeBody.clear();

	this->m_snakeBody.push_back(SnakeSegment(5, 7));
	this->m_snakeBody.push_back(SnakeSegment(5, 6));
	this->m_snakeBody.push_back(SnakeSegment(5, 5));
	this->setDirection(Direction::None); // Start off still.
	this->m_speed = 10;
	this->m_lives = 3;
	this->m_score = 0;
	this->m_lost = false;

}

void Snake::move()
{
	for (int i = this->m_snakeBody.size() - 1; i > 0; --i) {
		this->m_snakeBody[i].position = this->m_snakeBody[i - 1].position;
	}
	if (this->m_dir == Direction::Left) {
		--this->m_snakeBody[0].position.x;
	}
	else if (this->m_dir == Direction::Right) {
		++this->m_snakeBody[0].position.x;
	}
	else if (this->m_dir == Direction::Up) {
		--this->m_snakeBody[0].position.y;
	}
	else if (this->m_dir == Direction::Down) {
		++this->m_snakeBody[0].position.y;
	}
}

void Snake::tick()
{
	if (this->m_snakeBody.empty()) { return; }
	if (this->m_dir == Direction::None) { return; }
	this->move();
	this->checkCollision();
}

void Snake::cut(int l_segments)
{
	for (int i = 0; i < l_segments; ++i) {
		this->m_snakeBody.pop_back();
	}
	--this->m_lives;
	if (!this->m_lives) {
		this->lose();
		return;
	}

}

void Snake::render(sf::RenderWindow& l_window)
{
	if (this->m_snakeBody.empty()) { return; }

	auto head = this->m_snakeBody.begin();
	this->m_bodyRect.setFillColor(sf::Color::Yellow);
	this->m_bodyRect.setPosition(head->position.x * this->m_size, head->position.y * this->m_size);
	l_window.draw(this->m_bodyRect);

	this->m_bodyRect.setFillColor(sf::Color::Green);
	for (auto itr = this->m_snakeBody.begin() + 1; itr != this->m_snakeBody.end(); ++itr) {
		this->m_bodyRect.setPosition(itr->position.x * this->m_size, itr->position.y * this->m_size);
		l_window.draw(this->m_bodyRect);
	}
}

void Snake::checkCollision()
{
	if (this->m_snakeBody.size() < 5) { return; }
	SnakeSegment& head = this->m_snakeBody.front();
	for (auto itr = this->m_snakeBody.begin() + 1; itr != this->m_snakeBody.end(); ++itr) {
		if (itr->position == head.position) {
			int segments = this->m_snakeBody.end() - itr;
			this->cut(segments);
			break;
		}
	}
}
