#include "Window.h"

Window::Window()
{
	this->setup("Window", sf::Vector2u(800, 600));
}

Window::Window(const std::string& l_title, const sf::Vector2u& l_size)
{
	this->setup(l_title, l_size);
}

Window::~Window()
{
	this->destroy();
}

void Window::beginDraw()
{
	this->m_window.clear(sf::Color::Black);
}

void Window::endDraw()
{
	this->m_window.display();
}

void Window::update()
{
	sf::Event event;
	while (this->m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			this->m_isDone = true;
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5)
		{
			this->toggleFullscreen();
		}
	}
}

bool Window::isDone()
{
	return this->m_isDone;
}

bool Window::isFullscreen()
{
	return this->m_isFullscreen;
}

sf::Vector2u Window::getWindowSize()
{
	return this->m_windowSize;
}

void Window::toggleFullscreen()
{
	this->m_isFullscreen = !this->m_isFullscreen;
	this->destroy();
	this->create();
}

void Window::draw(sf::Drawable& l_drawable)
{
	this->m_window.draw(l_drawable);
}

sf::RenderWindow& Window::getRenderWindow()
{
	return this->m_window;
}

void Window::setup(const std::string& l_title, const sf::Vector2u& l_size)
{
	this->m_windowTitle = l_title;
	this->m_windowSize = l_size;
	this->m_isFullscreen = false;
	this->m_isDone = false;
	this->create();
}

void Window::destroy()
{
	this->m_window.close();
}

void Window::create()
{
	auto style = (this->m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	this->m_window.create({ this->m_windowSize.x, this->m_windowSize.y, 32 }, this->m_windowTitle, style);
}
