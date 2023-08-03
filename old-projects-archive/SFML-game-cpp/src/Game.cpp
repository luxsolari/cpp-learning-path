#include "Game.h"

Game::Game() : m_window("CMake SFML Project", sf::Vector2u(Globals::SCREEN_WIDTH_WINDOWED, Globals::SCREEN_HEIGHT_WINDOWED)), m_stateManager(&m_context)
{
	m_clock.restart();
	m_elapsed = sf::Time::Zero;
	m_context.m_windowManager = &m_window;
	m_context.m_eventManager = m_window.GetEventManager();
	m_stateManager.SwitchTo(StateType::Intro);
}

Game::~Game() {}

void Game::Update()
{
	m_window.Update();
	m_stateManager.Update(m_elapsed);
}

void Game::Render()
{
	m_window.BeginDraw();
	m_stateManager.Draw();
	m_window.EndDraw();
}

void Game::LateUpdate()
{
	m_stateManager.ProcessRequests();
	RestartClock();
}

void Game::HandleInput()
{

}

WindowManager* Game::GetWindow()
{
	return &m_window;
}

sf::Time Game::GetElapsed()
{
	return m_elapsed;
}

void Game::RestartClock()
{
	m_elapsed = m_clock.restart();
}
