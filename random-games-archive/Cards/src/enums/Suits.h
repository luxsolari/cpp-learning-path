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
// ConsoleColor setter
inline void SetColor(WORD color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// helper class
class ConsoleColor {
public:
    explicit ConsoleColor(WORD val) : m_val(val) { }

    void set() const {
        SetColor(m_val);
    }

private:
    WORD m_val;
};

// overload operator<< to get manipulator to work
inline std::wostream& operator<<(std::wostream& os, const ConsoleColor& c) {
    c.set();
    return os;
}

namespace ColorCodes {
    const ConsoleColor Red((WORD) Colors::RED);
    const ConsoleColor Black((WORD) Colors::BLACK);
    const ConsoleColor Blue((WORD) Colors::BLUE);
    const ConsoleColor Green((WORD) Colors::GREEN);
}

// suit symbol for Windows
const std::wstring HEARTS_SYMBOL     = L"\u2665";
const std::wstring CLUBS_SYMBOL      = L"\u2663";
const std::wstring DIAMONDS_SYMBOL   = L"\u2666";
const std::wstring SPADES_SYMBOL     = L"\u2660";

namespace SuitUtils {
    void printSuit(int suitToSelect) {
        _setmode(_fileno(stdout), _O_U16TEXT);
        switch (suitToSelect) {
            case static_cast<int>(Suits::HEARTS):
                std::wcout << ColorCodes::Red << HEARTS_SYMBOL << ColorCodes::Black;
                break;
            case static_cast<int>(Suits::DIAMONDS):
                std::wcout << ColorCodes::Red << DIAMONDS_SYMBOL << ColorCodes::Black;
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

namespace ColorSymbols {
    const std::wstring RED = L"\033[31m";
    const std::wstring GREEN = L"\033[32m";
    const std::wstring BLUE = L"\033[34m";
    const std::wstring YELLOW = L"\033[33m";
    const std::wstring MAGENTA = L"\033[35m";
    const std::wstring CYAN = L"\033[36m";
    const std::wstring WHITE = L"\033[37m";
    const std::wstring BLACK = L"\033[30m";
    const std::wstring RESET = L"\033[0m";
}

namespace StyleSymbols {
    const std::wstring BOLD = L"\033[1m";
    const std::wstring UNDERLINE = L"\033[4m";
    const std::wstring REVERSED = L"\033[7m";
    const std::wstring BLINK = L"\033[5m";
    const std::wstring RESET = L"\033[0m";
}

namespace SuitUtils {
    void printSuit(int suitToSelect) {
        switch (suitToSelect) {
            case static_cast<int>(Suits::HEARTS):
                std::cout << ColorSymbols::Red << HEART << ColorSymbols::White;
                break;
            case static_cast<int>(Suits::DIAMONDS):
                std::cout << ColorSymbols::Red << DIAMOND << ColorSymbols::White;
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
