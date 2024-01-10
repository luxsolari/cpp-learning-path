#include <iostream>
#include <string>
#ifdef _WIN32
#include "GameWin.h"
#include "enums/Suits.h"
#else
// Define card suits symbols glyphs for *nix
#define SPADE "♠︎"
#define CLUB "♣︎"
#define HEART "♥︎"
#define DIAMOND "♦︎"
// Define color codes for *nix
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define WHITE "\033[37m"

// Define card suits enum
enum SUIT { spade = 1, club, heart, diamond };

void printSuit(int suitToSelect) {
	switch (suitToSelect) {
	case spade:
		std::cout << SPADE;
		break;
	case club:
		std::cout << CLUB;
		break;
	case heart:
		std::cout << HEART;
		break;
	case diamond:
		std::cout << DIAMOND;
		break;
	default:
		std::cout << "Invalid suit." << std::endl;
		break;
	}
}
#endif
int main()
{
	std::cout << "Spades: ";   SuitUtils::printSuit(static_cast<int>(Suits::SPADES)); std::cout << "\n";
	std::cout << "Hearts: ";   SuitUtils::printSuit(static_cast<int>(Suits::HEARTS)); std::cout << "\n";
	std::cout << "Clubs: ";    SuitUtils::printSuit(static_cast<int>(Suits::CLUBS)); std::cout << "\n";
	std::cout << "Diamonds: "; SuitUtils::printSuit(static_cast<int>(Suits::DIAMONDS));;
	std::cout << "\n";

    // Get instance of GameWin
    GameWin* gameWin = GameWin::getInstance();
    // Print address of the instance
    std::cout << "GameWin address: " << gameWin->printAddress() << std::endl;

	system("pause");
	return 0;
}
