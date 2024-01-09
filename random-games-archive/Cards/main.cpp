#include <iostream>

#include <string>
#include <io.h>
#include <fcntl.h>
#include <Windows.h>

#define SPADE L"\u2660"
#define CLUB L"\u2663"
#define HEART L"\u2665"
#define DIAMOND L"\u2666"

enum SUIT { spade = 1, club, heart, diamond };

using namespace std;

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
		wcout << SPADE;
		break;
	case club:
		wcout << CLUB;
		break;
	case heart:
		wcout << red << HEART << white;
		break;
	case diamond:
		wcout << red << DIAMOND << white;
		break;
	default:
		wcout << "Invalid suit." << endl;
		break;
	}
	_setmode(_fileno(stdout), _O_TEXT);
}


int main()
{
#ifdef YOUR_MACRO
	cout << YOUR_MACRO << endl;
#endif
	cout << "Spades: ";   printSuit(spade); cout << "\n";
	cout << "Hearts: ";   printSuit(heart); cout << "\n";
	cout << "Clubs: ";    printSuit(club); cout << "\n";
	cout << "Diamonds: "; printSuit(diamond); 
	cout << "\n";
	system("pause");
}
