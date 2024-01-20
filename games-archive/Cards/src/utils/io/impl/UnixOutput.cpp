//
// Created by Lux Solari on 12/01/2024.
//

#ifdef UNIX_PLATFORM
#include <iostream>
#include "UnixOutput.h"

UnixOutput *UnixOutput::getInstance() {
    static UnixOutput instance;
    return &instance;
}

#endif //UNIX_PLATFORM
