#ifndef CMAKESFMLPROJECT_EVENTMANAGER_H
#define CMAKESFMLPROJECT_EVENTMANAGER_H
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>


enum class EventType
{
	KeyDown = sf::Event::KeyPressed,
	KeyUp = sf::Event::KeyReleased,
	MButtonDown = sf::Event::MouseButtonPressed,
	MButtonUp = sf::Event::MouseButtonReleased,
	MouseWheel = sf::Event::MouseWheelMoved,
	MouseMove = sf::Event::MouseMoved,
	WindowResized = sf::Event::Resized,
	GainedFocus = sf::Event::GainedFocus,
	LostFocus = sf::Event::LostFocus,
	MouseEntered = sf::Event::MouseEntered,
	MouseLeft = sf::Event::MouseLeft,
	Closed = sf::Event::Closed,
	TextEntered = sf::Event::TextEntered,
	Keyboard = sf::Event::Count + 1, Mouse, Joystick // These last 3 are for internal use only
};

struct EventInfo
{
	EventInfo() { m_code = 0; }
	EventInfo(int l_event) { m_code = l_event; }

	// This union is used to store the event code for the different event types.
	union {
		int m_code;
	};
};

using Events = std::vector<std::pair<EventType, EventInfo>>; // List of events that have occured this frame and their details.

struct EventDetails {
	EventDetails(const std::string& l_bindName)
		: m_name(l_bindName) {
		Clear();
	}
	std::string m_name;
	sf::Vector2i m_size;
	sf::Uint32 m_textEntered;
	sf::Vector2i m_mouse;
	int m_mouseWheelDelta;
	int m_keyCode; // Single key code.
	void Clear() {
		m_size = sf::Vector2i(0, 0);
		m_textEntered = 0;
		m_mouse = sf::Vector2i(0, 0);
		m_mouseWheelDelta = 0;
		m_keyCode = -1;
	}
};

struct Binding {
	explicit Binding(const std::string& l_name) : m_details(l_name), c(0), m_name(l_name) {}
	void BindEvent(EventType l_type, EventInfo l_info = EventInfo()) {
		m_events.emplace_back(l_type, l_info);
	}

	Events m_events;			// List of events that make up this binding.
	EventDetails m_details;     // Details for events that are "happening".
	int c;              // Count of events that are "happening".
	std::string m_name; // Name of the binding.
};

using Bindings = std::unordered_map<std::string, Binding*>;
using CallbackContainer = std::unordered_map<std::string, std::function<void(EventDetails*)>>;
enum class StateType;
using Callbacks = std::unordered_map<StateType, CallbackContainer>;

class EventManager {
public:
	EventManager();
	~EventManager();
	bool AddBinding(Binding* l_binding);
	bool RemoveBinding(std::string l_name);
	void SetFocus(const bool& l_focus);

	// Needs to be defined in the header!
	template<class T>
	bool AddCallback(StateType l_state, const std::string& l_name,
		void(T::* l_func)(EventDetails*), T* l_instance)
	{
		auto itr = m_callbacks.emplace(l_state, CallbackContainer()).first;
		auto temp = std::bind(l_func, l_instance,
			std::placeholders::_1);
		return itr->second.emplace(l_name, temp).second;
	}

	bool RemoveCallback(StateType l_state, const std::string& l_name) {
		auto itr = m_callbacks.find(l_state);
		if (itr == m_callbacks.end()) { return false; }
		auto itr2 = itr->second.find(l_name);
		if (itr2 == itr->second.end()) { return false; }
		itr->second.erase(l_name);
		return true;
	}

	void HandleEvent(sf::Event& l_event);
	void Update();

	sf::Vector2i GetMousePos(sf::RenderWindow* l_wind = nullptr) {
		return (l_wind ? sf::Mouse::getPosition(*l_wind) : sf::Mouse::getPosition());
	}

	void SetCurrentState(StateType l_state) { m_currentState = l_state; }

private:
	void LoadBindings();

	Bindings m_bindings;
	Callbacks m_callbacks;
	StateType m_currentState;
	bool m_hasFocus;
};

#endif //CMAKESFMLPROJECT_EVENTMANAGER_H