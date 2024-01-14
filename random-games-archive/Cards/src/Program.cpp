#include "utils/ConsoleFactory.h"

int main() {
    auto console = ConsoleFactory::createConsole();
    console->printToConsole("Hello World!\n");
    console->printToConsoleWide(L"\u2665");
    console->printToConsoleAtLocation(10, 10, "Hello World!\n");
    console->waitEnterKey();
    console->drawSquareBorder(10, 10, {10, 10});
    console->drawSquareBorder(10, 10, {20, 10});
    console->waitEnterKey();

    return 0;
}
