#include <iostream>
#include "utils/ConsoleFactory.h"

int main() {
    const Console* console = ConsoleFactory::createConsole();
    console->setConsoleSize(120, 25);
    console->setCursorPosition(0,0);
    console->drawSquareBorder(100, 25, {10,0});

    std::cout << "Press enter to exit...";
    std::cin.get();
    return 0;
}
