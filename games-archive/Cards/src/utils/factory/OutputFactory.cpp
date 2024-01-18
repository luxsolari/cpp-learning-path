//
// Created by luxsolari on 12/01/2024.
//

#include "OutputFactory.h"
#include "../io/impl/WindowsOutput.h"
#include "../io/impl/UnixOutput.h"

Output* OutputFactory::createConsole() {
#ifdef WINDOWS_PLATFORM
    return WindowsOutput::getInstance();
#else
    return UnixOutput::getInstance();
#endif
}
