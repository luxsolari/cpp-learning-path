#include <iostream>
#include "utils/ConsoleFactory.h"

int main() {
    auto console = ConsoleFactory::createConsole();
    console->printToConsole("Hello World!\n");
    console->printToConsoleAtLocation(10, 10, "Hello World!\n");

    console->waitEnterKey();
    return 0;
}
