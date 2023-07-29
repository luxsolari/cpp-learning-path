//
// Created by Lux Solari on 05/03/2023.
//

#ifndef CMAKESFMLPROJECT_STATE_H
#define CMAKESFMLPROJECT_STATE_H
#include <SFML/Graphics.hpp>

class State {
    // make the StateManager a friend class so it can access the private members
    friend class StateManager;
public:
    State(StateManager * l_stateManager) 
        : l_stateManager(l_stateManager), m_transparent(false), m_transcendent(false) {}
    virtual ~State() {}

    virtual void OnCreate() = 0;
    virtual void OnDestroy() = 0;

    virtual void Activate() = 0;
    virtual void Deactivate() = 0;

    virtual void Update(const sf::Time& l_time) = 0;
    virtual void Draw() = 0;

    void SetTransparent(const bool& l_transparent) { m_transparent = l_transparent; }
    bool IsTransparent() const { return m_transparent; }

    void SetTranscendent(const bool& l_transcendent) { m_transcendent = l_transcendent; }
    bool IsTranscendent() const { return m_transcendent; }

    StateManager* GetStateManager() { return l_stateManager; }

protected:
    StateManager* l_stateManager;
    bool m_transparent;  // if true, the state below this one will still be rendered
    bool m_transcendent; // if true, the state below this one will not be updated
    
};

#endif //CMAKESFMLPROJECT_STATE_H
