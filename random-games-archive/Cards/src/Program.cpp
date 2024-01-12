#include <iostream>
#include "enums/Suits.h"

#ifdef WINDOWS_PLATFORM
#include "GameWin.h"
#else
#include "GameUnix.h"
#endif

int main() {
#ifdef WINDOWS_PLATFORM
    // Get instance of GameWin
    const GameWin *gameWin = GameWin::getInstance();
    // Set console window size
    std::vector<int> consoleSize = gameWin->getConsoleSize();
    int gameBorderWidth = consoleSize.at(0) - 1;
    int gameBorderHeight = consoleSize.at(1) - 10;

    gameWin->setConsoleSize(gameBorderWidth, gameBorderHeight);
    // draw border
    gameWin->drawBorder(
            gameBorderWidth - 1,
            gameBorderHeight - 1);
    // move cursor to top left corner
    gameWin->setCursorPosition(0, 0);
    // draw at position 5, 5
    gameWin->moveCursorDown(5);
    gameWin->moveCursorRight(5);
    std::cout << "Hello world!";
    gameWin->moveCursorDown(1);
    gameWin->returnCarriage();
    gameWin->moveCursorRight(5);
    std::cout << "Example Card: ";
    gameWin->moveCursorDown(1);
    gameWin->returnCarriage();
    gameWin->moveCursorRight(5);
    std::cout << "A";
    SuitUtils::printSuit(static_cast<int>(Suits::CLUBS));
    std::cout << " ";
    std::cout << "A";
    SuitUtils::printSuit(static_cast<int>(Suits::HEARTS));
    gameWin->moveCursorDown(1);
    gameWin->returnCarriage();
    gameWin->moveCursorRight(5);
    gameWin->drawCard(gameWin->getCursorPosition().at(0), gameWin->getCursorPosition().at(1), 5, 5);
    gameWin->moveCursorUp(4);
    gameWin->moveCursorRight(1);
    gameWin->drawCard(gameWin->getCursorPosition().at(0), gameWin->getCursorPosition().at(1), 5, 5);
    // reset cursor position to end of console
    gameWin->setCursorPosition(0, gameBorderHeight - 1);
#else
    // Get instance of GameUnix
    const GameUnix* gameUnix = GameUnix::getInstance();
    // Print address of the instance
    std::cout << "GameUnix address: " << gameUnix->printAddress() << std::endl;
    // Print size of console window
    std::cout << "Console window size: " << GameUnix::getConsoleSize() << std::endl;
#endif
    std::cout << "Press enter to exit...";
    std::cin.get();
    return 0;
}
