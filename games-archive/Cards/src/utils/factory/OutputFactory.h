//
// Created by luxsolari on 12/01/2024.
//

#ifndef CARDS_CONSOLEFACTORY_H
#define CARDS_CONSOLEFACTORY_H


#include "../io/Output.h"

class OutputFactory {

    // Singleton
public:
    OutputFactory(const OutputFactory&) = delete;
    OutputFactory(OutputFactory&&) = delete;
    OutputFactory() = delete;
    OutputFactory& operator=(const OutputFactory&) = delete;
    OutputFactory& operator=(OutputFactory&&) = delete;
    ~OutputFactory() = delete;

    // Strategy method to create a console object based on the platform the program is running
    static Output* createOutput();

};


#endif //CARDS_CONSOLEFACTORY_H
