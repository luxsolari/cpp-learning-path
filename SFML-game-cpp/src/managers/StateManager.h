//
// Created by Lux Solari on 04/03/2023.
//

#ifndef CMAKESFMLPROJECT_STATEMANAGER_H
#define CMAKESFMLPROJECT_STATEMANAGER_H
#include <vector>
#include <memory>
#include <unordered_map>
#include "WindowManager.h"
#include "EventManager.h"
#include "Globals.h"
#include "State.h"
#include "StateType.h"

struct SharedContext {
	SharedContext() : m_windowManager(nullptr), m_eventManager(nullptr) {}
	WindowManager* m_windowManager;
	EventManager* m_eventManager;
};

using StateContainer = std::vector<std::pair<StateType, State*>>;
using TypeContainer = std::vector<StateType>;
using StateFactory = std::unordered_map<StateType, std::function<State* (void)>>;

class StateManager
{
public:
	StateManager(SharedContext* l_shared);
	~StateManager();
	void Update(const sf::Time& l_time);
	void Draw();
	void ProcessRequests();
	SharedContext* GetContext();
	bool HasState(const StateType& l_type);
	void SwitchTo(const StateType& l_type);
	void Remove(const StateType& l_type);

private:
	// Methods.
	void CreateState(const StateType& l_type);
	void RemoveState(const StateType& l_type);
	template<class T>
	void RegisterState(const StateType& l_type) {
		m_stateFactory[l_type] = [this]() -> State*
		{
			return new T(this);
		};
	}
	// Members.
	SharedContext* m_shared;
	StateContainer m_states;
	TypeContainer m_toRemove;
	StateFactory m_stateFactory;
};


#endif //CMAKESFMLPROJECT_STATEMANAGER_H
