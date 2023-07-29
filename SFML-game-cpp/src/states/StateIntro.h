#include "State.h"
#include "EventManager.h"

class StateIntro : public State
{
public:
	void OnCreate() override;
	void OnDestroy() override;
	void Update(const sf::Time& l_time) override;
	void Draw() override;
	void Activate() override {};
	void Deactivate() override {};
	void Continue(EventDetails* l_details);

	// constructor 
	StateIntro(StateManager* l_stateManager) : State(l_stateManager) {}
	~StateIntro() {}

private:

	sf::Texture m_introTexture;
	sf::Sprite m_introSprite;

	sf::Font m_font;
	sf::Text m_text;

	float m_timePassed;

};
