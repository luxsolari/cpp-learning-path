//
// Created by luxsolari on 1/16/2024.
//

#include "InputFactory.h"
#include "../io/impl/WindowsInput.h"
#include "../io/impl/UnixInput.h"

Input *InputFactory::createInput() {
#ifdef WINDOWS_PLATFORM
    return WindowsInput::GetInstance(true);
#else
    return UnixInput::getInstance();
#endif
}
