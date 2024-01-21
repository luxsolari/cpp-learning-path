//
// Created by luxsolari on 1/21/2024.
//

#ifndef CARDS_SLN_GAMEINSTANCE_H
#define CARDS_SLN_GAMEINSTANCE_H


class GameInstance {
public:

private:
    // pointers to input, output and audio subsystems
    class Output *m_output; // pointer to the output subsystem. It will be used to render "graphics" (text) to the screen.
    class Input  *m_input;  // pointer to the input subsystem. It will be used to get input from the user.
    class Audio  *m_audio;  // pointer to the audio subsystem. It will be used to play sounds and music.
    class StateManager *m_stateManager; // pointer to the state manager. It will be used to change the state of the game.
};


#endif //CARDS_SLN_GAMEINSTANCE_H
