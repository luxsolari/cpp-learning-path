//
// Created by luxsolari on 1/16/2024.
//

#ifndef CARDS_SLN_INPUTFACTORY_H
#define CARDS_SLN_INPUTFACTORY_H


#include "../io/Input.h"

class InputFactory {
    // Singleton
public:
    InputFactory(const InputFactory&) = delete;
    InputFactory(InputFactory&&) = delete;
    InputFactory() = delete;
    InputFactory& operator=(const InputFactory&) = delete;
    InputFactory& operator=(InputFactory&&) = delete;
    ~InputFactory() = delete;

    // Strategy method to create a console object based on the platform the program is running
    static Input* createInput();
};


#endif //CARDS_SLN_INPUTFACTORY_H
