#include "StateIntro.h"
#include "StateManager.h"

void StateIntro::OnCreate()
{
	this->m_timePassed = 0.0f;
	sf::Vector2u windowSize = this->l_stateManager->GetContext()->m_windowManager->GetWindowSize();
	m_introTexture.loadFromFile("assets/intro-small.png");
	m_introSprite.setTexture(m_introTexture);

	m_introSprite.setOrigin(m_introTexture.getSize().x / 2.0f, m_introTexture.getSize().y / 2.0f);
	m_introSprite.setPosition(windowSize.x / 2.0f, 0 - m_introTexture.getSize().y / 2.0f);

	m_font.loadFromFile("assets/fonts/arial.ttf");
	m_text.setFont(m_font);
	m_text.setString("Press SPACE to continue");
	m_text.setCharacterSize(24);

	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

	m_text.setPosition(windowSize.x / 2.0f, (windowSize.y / 2.0f) + this->m_introSprite.getLocalBounds().height / 2.0f);

	EventManager* evMgr = this->l_stateManager->GetContext()->m_eventManager;
	evMgr->AddCallback(StateType::Intro, "Intro_Continue", &StateIntro::Continue, this);

}

void StateIntro::OnDestroy()
{
	EventManager* evMgr = l_stateManager->
		GetContext()->m_eventManager;
	evMgr->RemoveCallback(StateType::Intro, "Intro_Continue");
}

void StateIntro::Update(const sf::Time& l_time)
{
	if (m_timePassed < 2.0f) {
		m_timePassed += l_time.asSeconds();

		// move sprite down until it reaches the center of the screen
		sf::Vector2f pos = m_introSprite.getPosition();
		pos.y += 240.0f * l_time.asSeconds();
		m_introSprite.setPosition(pos);
	}
	else if (m_timePassed < 5.0f) {
		m_timePassed += l_time.asSeconds();
	}
}

void StateIntro::Draw()
{
	sf::RenderWindow* window = this->l_stateManager->GetContext()->m_windowManager->GetRenderWindow();
	window->draw(m_introSprite);
	if (m_timePassed >= 5.0f) {
		// fade in text
		sf::Color color = m_text.getFillColor();
		color.a += 2;
		if (color.a >= 255) {
			color.a = 255;
		}
		m_text.setFillColor(color);
		window->draw(m_text);
	}
}

void StateIntro::Continue(EventDetails* l_details)
{
	if (m_timePassed >= 5.0f) {
		this->l_stateManager->SwitchTo(StateType::MainMenu);
		this->l_stateManager->Remove(StateType::Intro);
	}
}
