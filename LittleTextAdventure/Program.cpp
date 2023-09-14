#include <thread>
#include <chrono>
#include <string>
#include <iostream>
#include "CommandDictionary.h"
#include "StatesManager.h"

int main ()
{
	StatesManager* statesManager = StatesManager::GetInstance();

	statesManager->Update();

	std::cout << "--- Game Terminated, press any key to exit. --" << std::endl;
	std::cin.get();
	
	return 0;
}
