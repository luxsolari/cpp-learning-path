//
// Created by luxsolari on 09/01/2024.
//

#ifndef CARDS_SUITS_H
#define CARDS_SUITS_H
#include <string>
#include <iostream>

// if WINDOWS
#ifdef _WIN32
#include <io.h>
#include <Windows.h>
#include <minwindef.h>
#include <fcntl.h>
#endif

enum class Suits {
    HEARTS = 1,
    DIAMONDS,
    CLUBS,
    SPADES
};

enum class Colors {
    BLUE = 1,
    GREEN = 2,
    RED = 4,
    BLACK = 7
};

#ifdef _WIN32
// color setter
inline void SetColor(WORD color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// helper class
class color {
public:
    explicit color(WORD val) : m_val(val) { }

    void set() const {
        SetColor(m_val);
    }

private:
    WORD m_val;
};

// overload operator<< to get manipulator to work
inline std::wostream& operator<<(std::wostream& os, const color& c) {
    c.set();
    return os;
}

// instances of helper class to avoid need to remember 4 is red, etc
static const color red((WORD) Colors::RED);
static const color black((WORD) Colors::BLACK);
static const color blue((WORD) Colors::BLUE);
static const color green((WORD) Colors::GREEN);

// suit symbol for Windows
const std::wstring HEARTS_SYMBOL     = L"\u2665";
const std::wstring DIAMONDS_SYMBOL   = L"\u2666";
const std::wstring CLUBS_SYMBOL      = L"\u2663";
const std::wstring SPADES_SYMBOL     = L"\u2660";

namespace SuitUtils {
    void printSuit(int suitToSelect) {
        _setmode(_fileno(stdout), _O_U16TEXT);
        switch (suitToSelect) {
            case static_cast<int>(Suits::HEARTS):
                std::wcout << red << HEARTS_SYMBOL << black;
                break;
            case static_cast<int>(Suits::DIAMONDS):
                std::wcout << red << DIAMONDS_SYMBOL << black;
                break;
            case static_cast<int>(Suits::CLUBS):
                std::wcout << CLUBS_SYMBOL;
                break;
            case static_cast<int>(Suits::SPADES):
                std::wcout << SPADES_SYMBOL;
                break;
            default:
                std::wcout << "Invalid suit." << std::endl;
                break;
        }
        _setmode(_fileno(stdout), _O_TEXT);
    }
}
// if UNIX
#else
// Define card suits symbols glyphs for *nix
const std::string SPADE = "♠︎";
const std::string CLUB = "♣︎";
const std::string HEART = "♥︎";
const std::string DIAMOND = "♦︎";

// Define color codes for *nix
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string BLUE = "\033[34m";
const std::string WHITE = "\033[37m";

namespace SuitUtils {
    void printSuit(int suitToSelect) {
        switch (suitToSelect) {
            case static_cast<int>(Suits::HEARTS):
                std::cout << RED << HEART << WHITE;
                break;
            case static_cast<int>(Suits::DIAMONDS):
                std::cout << RED << DIAMOND << WHITE;
                break;
            case static_cast<int>(Suits::CLUBS):
                std::cout << CLUB;
                break;
            case static_cast<int>(Suits::SPADES):
                std::cout << SPADE;
                break;
            default:
                std::cout << "Invalid suit." << std::endl;
                break;
        }
    }
}

#endif

#endif //CARDS_SUITS_H
