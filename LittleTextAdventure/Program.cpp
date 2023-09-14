#include <thread>
#include <chrono>
#include <string>
#include <iostream>
#include "CommandDictionary.h"
#include "StatesManager.h"

int main ()
{
	CommandDictionary* commandDictionary = CommandDictionary::GetInstance();
	StatesManager* statesManager = StatesManager::GetInstance();

	statesManager->Update();
	
	return 0;
}
