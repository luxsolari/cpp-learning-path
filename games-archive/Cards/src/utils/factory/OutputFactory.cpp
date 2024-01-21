//
// Created by luxsolari on 12/01/2024.
//

#include "OutputFactory.h"
#include "../io/impl/WindowsOutput.h"
#include "../io/impl/UnixOutput.h"

Output* OutputFactory::createOutput() {
#ifdef WINDOWS_PLATFORM
    return WindowsOutput::getInstance(true);
#else
    return UnixOutput::getInstance(true);
#endif
}
