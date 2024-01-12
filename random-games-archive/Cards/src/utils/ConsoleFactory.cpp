//
// Created by luxsolari on 12/01/2024.
//

#include "ConsoleFactory.h"
#include "WindowsConsole.h"

const Console* ConsoleFactory::createConsole() {
#ifdef WINDOWS_PLATFORM
    return WindowsConsole::getInstance();
#else
    //return new LinuxConsole();
#endif
}
