//
// Created by luxsolari on 09/01/2024.
//
#ifdef WINDOWS_PLATFORM
#include "WindowsOutput.h"

WindowsOutput* WindowsOutput::getInstance() {
    static WindowsOutput instance;
    return &instance;
}

#endif //WINDOWS_PLATFORM
