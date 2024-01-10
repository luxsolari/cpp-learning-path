//
// Created by luxsolari on 09/01/2024.
//

#ifndef CARDS_SUITS_H
#define CARDS_SUITS_H

// if WINDOWS
#ifdef _WIN32
#include <string>
#include <iostream>
#include <io.h>
#include <Windows.h>
#include <minwindef.h>
#include <fcntl.h>

enum class Suits {
    HEARTS = 1,
    DIAMONDS,
    CLUBS,
    SPADES
};

enum class Colors {
    RED = 4,
    BLACK = 7
};

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
static const color blue(1);
static const color green(2);

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

#endif

#endif //CARDS_SUITS_H
