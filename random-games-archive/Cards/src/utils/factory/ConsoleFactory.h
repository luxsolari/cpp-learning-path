//
// Created by luxsolari on 12/01/2024.
//

#ifndef CARDS_CONSOLEFACTORY_H
#define CARDS_CONSOLEFACTORY_H


#include "../io/Console.h"

class ConsoleFactory {

    // Singleton
public:
    ConsoleFactory(const ConsoleFactory&) = delete;
    ConsoleFactory(ConsoleFactory&&) = delete;
    ConsoleFactory() = delete;
    ConsoleFactory& operator=(const ConsoleFactory&) = delete;
    ConsoleFactory& operator=(ConsoleFactory&&) = delete;
    ~ConsoleFactory() = delete;

    // Strategy method to create a console object based on the platform the program is running
    static Console* createConsole();

};


#endif //CARDS_CONSOLEFACTORY_H
