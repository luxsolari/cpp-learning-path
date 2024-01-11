#include <iostream>
#include "enums/Suits.h"
#ifdef WINDOWS_PLATFORM
#include "GameWin.h"
#else
#include "GameUnix.h"
#endif
int main()
{
#ifdef WINDOWS_PLATFORM
    // Get instance of GameWin
    auto gameWin = GameWin::getInstance();
    // Print address of the instance
    std::cout << "GameWin address: " << gameWin->printAddress() << std::endl;
#else
    // Get instance of GameUnix
    const GameUnix* gameUnix = GameUnix::getInstance();
    // Print address of the instance
    std::cout << "GameUnix address: " << gameUnix->printAddress() << std::endl;
    // Print size of console window
    std::cout << "Console window size: " << GameUnix::getConsoleSize() << std::endl;
#endif
    std::cout << "Press enter to exit...";
	std::cin.get();
	return 0;
}
