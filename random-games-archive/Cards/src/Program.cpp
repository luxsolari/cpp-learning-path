#include <iostream>
#include <string>
#include "enums/Suits.h"

#ifdef _WIN32
#include "GameWin.h"
#else
#include "GameUnix.h"
#endif
int main()
{
	std::cout << "Spades: "  ;
    SuitUtils::printSuit(static_cast<int>(Suits::SPADES));
    std::cout << "\n";

	std::cout << "Hearts: "  ;
    SuitUtils::printSuit(static_cast<int>(Suits::HEARTS));
    std::cout << "\n";

	std::cout << "Clubs: "   ;
    SuitUtils::printSuit(static_cast<int>(Suits::CLUBS));
    std::cout << "\n";

	std::cout << "Diamonds: ";
    SuitUtils::printSuit(static_cast<int>(Suits::DIAMONDS));
	std::cout << "\n";

#ifdef _WIN32
    // Get instance of GameWin
    auto gameWin = GameWin::getInstance();
    // Print address of the instance
    std::cout << "GameWin address: " << gameWin->printAddress() << std::endl;
#else
    // Get instance of GameUnix
    GameUnix* gameUnix = GameUnix::getInstance();
    // Print address of the instance
    std::cout << "GameUnix address: " << gameUnix->printAddress() << std::endl;
#endif
    std::cout << "Press enter to exit...";
	std::cin.get();
	return 0;
}
