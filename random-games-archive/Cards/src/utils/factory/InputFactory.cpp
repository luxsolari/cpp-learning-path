//
// Created by luxsolari on 1/16/2024.
//

#include "InputFactory.h"
#include "../io/impl/WindowsInput.h"

Input *InputFactory::createInput() {
#ifdef WINDOWS_PLATFORM
    return WindowsInput::GetInstance();
#else
    return nullptr;
#endif
}
