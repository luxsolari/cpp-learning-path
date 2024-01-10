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
	std::cout << "Spades: ";   SuitUtils::printSuit(static_cast<int>(Suits::SPADES)); std::cout << "\n";
	std::cout << "Hearts: ";   SuitUtils::printSuit(static_cast<int>(Suits::HEARTS)); std::cout << "\n";
	std::cout << "Clubs: ";    SuitUtils::printSuit(static_cast<int>(Suits::CLUBS)); std::cout << "\n";
	std::cout << "Diamonds: "; SuitUtils::printSuit(static_cast<int>(Suits::DIAMONDS));;
	std::cout << "\n";

    // Get instance of GameWin
    //GameWin* gameWin = GameWin::getInstance();
    // Print address of the instance
    //std::cout << "GameWin address: " << gameWin->printAddress() << std::endl;

    // Get instance of GameUnix
    GameUnix* gameUnix = GameUnix::getInstance();

	system("pause");
	return 0;
}
