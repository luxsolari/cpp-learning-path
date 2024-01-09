#include <iostream>
#include <string>
#include <fcntl.h>
#ifdef _WIN32
#include <io.h>
#include <Windows.h>
#include "GameWin.h"

#define SPADE L"\u2660"
#define CLUB L"\u2663"
#define HEART L"\u2665"
#define DIAMOND L"\u2666"
enum SUIT { spade = 1, club, heart, diamond };

// color setter
inline void SetColor(WORD color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// helper class
class color {
public:
	color(WORD val) : m_val(val) { }

	void set() const {
		SetColor(m_val);
	}

private:
	WORD m_val;
};

// instances of helper class to avoid need to remember 4 is red, etc
static const color red(4);
static const color green(2);
static const color blue(1);
static const color white(7);
// etc

// overload operator<< to get manipulator to work
inline std::wostream& operator<<(std::wostream& os, const color& c) {
	c.set();
	return os;
}

void printSuit(int suitToSelect) {
	_setmode(_fileno(stdout), _O_U16TEXT);
	switch (suitToSelect) {
	case spade:
		std::wcout << SPADE;
		break;
	case club:
		std::wcout << CLUB;
		break;
	case heart:
		std::wcout << red << HEART << white;
		break;
	case diamond:
		std::wcout << red << DIAMOND << white;
		break;
	default:
		std::wcout << "Invalid suit." << std::endl;
		break;
	}
	_setmode(_fileno(stdout), _O_TEXT);
}
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
#ifdef _WIN32
	std::cout << "Spades: ";   printSuit(spade); std::cout << "\n";
	std::cout << "Hearts: ";   printSuit(heart); std::cout << "\n";
	std::cout << "Clubs: ";    printSuit(club); std::cout << "\n";
	std::cout << "Diamonds: "; printSuit(diamond);
	std::cout << "\n";

    GameWin::getInstance()->printName();

	system("pause");
#else
	// Display card suits symbols glyphs
	std::cout << "Spades: " << SPADE << std::endl;
	std::cout << "Hearts: " << HEART << std::endl;
	std::cout << "Clubs: " << CLUB << std::endl;
	std::cout << "Diamonds: " << DIAMOND << std::endl;
#endif

}
