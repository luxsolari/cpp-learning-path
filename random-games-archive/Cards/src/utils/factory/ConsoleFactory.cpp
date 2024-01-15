//
// Created by luxsolari on 12/01/2024.
//

#include "ConsoleFactory.h"
#include "../io/impl/WindowsConsole.h"
#include "../io/impl/UnixConsole.h"

Console* ConsoleFactory::createConsole() {
#ifdef WINDOWS_PLATFORM
    return WindowsConsole::getInstance();
#else
    return UnixConsole::getInstance();
#endif
}
