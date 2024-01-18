//
// Created by Lux Solari on 05/03/2023.
//

#ifndef CMAKESFMLPROJECT_GLOBALS_H
#define CMAKESFMLPROJECT_GLOBALS_H
namespace Globals {

    constexpr unsigned int SCREEN_WIDTH_WINDOWED = 1280;
    constexpr unsigned int SCREEN_HEIGHT_WINDOWED = 720;

    constexpr unsigned int SCREEN_WIDTH = 1920;
    constexpr unsigned int SCREEN_HEIGHT = 1080;

    constexpr unsigned int MAX_FRAME_RATE = 120;
    constexpr unsigned int MAX_TICK_RATE = 60;

    static constexpr int SAMPLE_INTERVAL = 1000000;
}

namespace Logger {
    #ifdef DEBUG
    #define LOG(msg) std::cout << msg << std::endl;
    #else
    #define LOG(msg)
    #endif
}
#endif //CMAKESFMLPROJECT_GLOBALS_H

