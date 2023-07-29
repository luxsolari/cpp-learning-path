//
// Created by Lux Solari on 05/03/2023.
//

#ifndef CMAKESFMLPROJECT_WINDOWMANAGER_H
#define CMAKESFMLPROJECT_WINDOWMANAGER_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Globals.h"
#include "EventManager.h"

class WindowManager {
public:
	WindowManager();
	WindowManager(const std::string& l_title, const sf::Vector2u& l_size);
	~WindowManager();

	void BeginDraw();
	void EndDraw();

	void Update();

	bool IsDone();
	bool IsFullscreen();
	sf::Vector2u GetWindowSize();
	sf::RenderWindow* GetRenderWindow();

	void ToggleFullscreen(EventDetails* l_details);
	void Close(EventDetails* l_details = nullptr);
	
	void Draw (sf::Drawable& l_drawable);

	EventManager* GetEventManager();
	bool IsFocused();

private:
	void Setup(const std::string& l_title, const sf::Vector2u& l_size);
	void Destroy();
	void Create();

	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;
	bool m_isFullscreen;

	EventManager m_eventManager;
	bool m_isFocused;

};


#endif //CMAKESFMLPROJECT_WINDOWMANAGER_H
