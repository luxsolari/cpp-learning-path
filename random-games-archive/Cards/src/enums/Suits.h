//
// Created by luxsolari on 09/01/2024.
//

#ifndef CARDS_SUITS_H
#define CARDS_SUITS_H
#include <string>
#include <iostream>

// if WINDOWS
#ifdef WINDOWS_PLATFORM
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

#ifdef WINDOWS_PLATFORM
// suit symbol for Windows
const std::wstring HEARTS_SYMBOL     = L"\u2665";
const std::wstring CLUBS_SYMBOL      = L"\u2663";
const std::wstring DIAMONDS_SYMBOL   = L"\u2666";
const std::wstring SPADES_SYMBOL     = L"\u2660";
// hollow suits
const std::wstring HEARTS_SYMBOL2    = L"\u2661";
const std::wstring CLUBS_SYMBOL2     = L"\u2667";
const std::wstring DIAMONDS_SYMBOL2  = L"\u2662";
const std::wstring SPADES_SYMBOL2    = L"\u2664";
// borders
const std::wstring TOP_LEFT_CORNER   = L"\u250C";
const std::wstring TOP_RIGHT_CORNER  = L"\u2510";
const std::wstring BOTTOM_LEFT_CORNER= L"\u2514";
const std::wstring BOTTOM_RIGHT_CORNER= L"\u2518";
const std::wstring HORIZONTAL_BORDER = L"\u2500";
const std::wstring VERTICAL_BORDER   = L"\u2502";
const std::wstring TOP_BORDER        = L"\u252C";
const std::wstring BOTTOM_BORDER     = L"\u2534";
const std::wstring LEFT_BORDER       = L"\u251C";
const std::wstring RIGHT_BORDER      = L"\u2524";

// SuitColor setter
inline void SetColor(WORD color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// helper class
class SuitColor {
public:
    explicit SuitColor(WORD val) : m_val(val) { }

    void set() const {
        SetColor(m_val);
    }

private:
    WORD m_val;
};

// overload operator<< to get manipulator to work
inline std::wostream& operator<<(std::wostream& os, const SuitColor& c) {
    c.set();
    return os;
}

namespace ColorUtils {
    const SuitColor Red((WORD) Colors::RED);
    const SuitColor Black((WORD) Colors::BLACK);
    const SuitColor Blue((WORD) Colors::BLUE);
    const SuitColor Green((WORD) Colors::GREEN);
}


namespace SuitUtils {
    void printSuit(int suitToSelect) {
        _setmode(_fileno(stdout), _O_U16TEXT);
        switch (suitToSelect) {
            case static_cast<int>(Suits::HEARTS):
                std::wcout << ColorUtils::Red << HEARTS_SYMBOL << ColorUtils::Black;
                break;
            case static_cast<int>(Suits::DIAMONDS):
                std::wcout << ColorUtils::Red << DIAMONDS_SYMBOL << ColorUtils::Black;
                break;
            case static_cast<int>(Suits::CLUBS):
                std::wcout << CLUBS_SYMBOL;
                break;
            case static_cast<int>(Suits::SPADES):
                std::wcout << SPADES_SYMBOL;
                break;
            default:
                std::cout << "Invalid suit." << std::endl;
                break;
        }
        _setmode(_fileno(stdout), _O_TEXT);
    }

    void printBorders() {
        _setmode(_fileno(stdout), _O_U16TEXT);
        std::wcout << TOP_LEFT_CORNER << HORIZONTAL_BORDER << HORIZONTAL_BORDER<< HORIZONTAL_BORDER  << HORIZONTAL_BORDER << HORIZONTAL_BORDER << TOP_RIGHT_CORNER << std::endl;
        std::wcout << VERTICAL_BORDER << "X    " << VERTICAL_BORDER << std::endl;
        std::wcout << VERTICAL_BORDER << "  " << ColorUtils::Red << DIAMONDS_SYMBOL << ColorUtils::Black << "  " << VERTICAL_BORDER << std::endl;
        std::wcout << VERTICAL_BORDER << "    X" << VERTICAL_BORDER << std::endl;
        std::wcout << BOTTOM_LEFT_CORNER << HORIZONTAL_BORDER << HORIZONTAL_BORDER << HORIZONTAL_BORDER << HORIZONTAL_BORDER << HORIZONTAL_BORDER << BOTTOM_RIGHT_CORNER << std::endl;
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
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string BLUE = "\033[34m";
    const std::string YELLOW = "\033[33m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    const std::string WHITE = "\033[37m";
    const std::string BLACK = "\033[30m";
    const std::string RESET = "\033[0m";
}

namespace StyleSymbols {
    const std::string BOLD = "\033[1m";
    const std::string UNDERLINE = "\033[4m";
    const std::string REVERSED = "\033[7m";
    const std::string BLINK = "\033[5m";
    const std::string RESET = "\033[0m";
}

namespace SuitUtils {
    void printSuit(int suitToSelect) {
        switch (suitToSelect) {
            case static_cast<int>(Suits::HEARTS):
                std::cout << ColorSymbols::RED << HEART << ColorSymbols::RESET;
                break;
            case static_cast<int>(Suits::DIAMONDS):
                std::cout << ColorSymbols::RED << DIAMOND << ColorSymbols::RESET;
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
