//
// Created by luxsolari on 1/15/2024.
//

#include "GameManagerFactory.h"
#include "../impl/WindowsGameManager.h"
#include "../impl/UnixGameManager.h"

GameManager *GameManagerFactory::createGameManager() {
#ifdef UNIX_PLATFORM
    return new UnixGameManager();
#endif //UNIX_PLATFORM
#ifdef WINDOWS_PLATFORM
    return new WindowsGameManager();
#endif //WINDOWS_PLATFORM
}
