//
// Created by Lux Solari on 05/03/2023.
//

#include "WindowManager.h"
#include "StateManager.h"

WindowManager::WindowManager()
{
	Setup("Window", sf::Vector2u(1280, 720));
}

WindowManager::WindowManager(const std::string& l_title, const sf::Vector2u& l_size)
{
	Setup(l_title, l_size);
}

WindowManager::~WindowManager()
{
	Destroy();
}

void WindowManager::Setup(const std::string& l_title, const sf::Vector2u& l_size)
{
	m_windowTitle = l_title;
	m_windowSize = l_size;
	m_isFullscreen = false;
	m_isDone = false;
	m_isFocused = true;
	m_eventManager.AddCallback(StateType(0), "Fullscreen_toggle", &WindowManager::ToggleFullscreen, this);
	m_eventManager.AddCallback(StateType(0), "Window_close", &WindowManager::Close, this);
	Create();
}

void WindowManager::Create()
{
	auto style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	m_window.create({ m_windowSize.x, m_windowSize.y, 32 }, m_windowTitle, style);
	m_window.setFramerateLimit(Globals::MAX_FRAME_RATE);
}

void WindowManager::Destroy()
{
	m_window.close();
}

void WindowManager::Update()
{
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::LostFocus) {
			m_isFocused = false;
			m_eventManager.SetFocus(false);
		}
		else if (event.type == sf::Event::GainedFocus) {
			m_isFocused = true;
			m_eventManager.SetFocus(true);
		}
		m_eventManager.HandleEvent(event);
	}
	m_eventManager.Update();
}

void WindowManager::ToggleFullscreen(EventDetails* l_details)
{
	m_isFullscreen = !m_isFullscreen;
	Destroy();
	Create();
}

void WindowManager::Close(EventDetails* l_details)
{
	m_isDone = true;
}

void WindowManager::BeginDraw()
{
	m_window.clear(sf::Color(17, 13, 5));
}

void WindowManager::EndDraw()
{
	m_window.display();
}

bool WindowManager::IsDone()
{
	return m_isDone;
}

bool WindowManager::IsFullscreen()
{
	return m_isFullscreen;
}

sf::Vector2u WindowManager::GetWindowSize()
{
	return m_windowSize;
}

sf::RenderWindow* WindowManager::GetRenderWindow()
{
	return &m_window;
}

void WindowManager::Draw(sf::Drawable& l_drawable)
{
	m_window.draw(l_drawable);
}

EventManager* WindowManager::GetEventManager()
{
	return &m_eventManager;
}

bool WindowManager::IsFocused()
{
	return m_isFocused;
}
