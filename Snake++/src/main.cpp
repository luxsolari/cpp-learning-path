//#include <SFML/Graphics.hpp>
//#include "core/Game.h"
//
//
//int main() 
//{
//	Game game;
//	while (!game.getWindow()->isDone())
//	{
//		game.handleInput();
//		game.update();
//		game.render();
//		game.restartClock();
//	}
//}

#include <iostream>

// Function using double pointer
void modifyDoublePointer(int** ptr) {
    int* newPtr = new int[5];
    newPtr[0] = 123;
    ptr = &newPtr;
}

// Function using double pointer reference
void modifyDoublePointerReference(int**& ptr) {
    int* newPtr = new int[5];
    newPtr[0] = 123;
    *ptr = newPtr;
}

int main() {
    int** myArray = new int* [5];
    myArray[0] = new int[5]; // Allocating memory for the first row

    // Using double pointer
    modifyDoublePointer(myArray);
    std::cout << myArray[0][0] << std::endl; // Output: 0

    // Using double pointer reference
    modifyDoublePointerReference(myArray);
    std::cout << myArray[0][0] << std::endl; // Output: 123

    // Deallocate memory properly to prevent memory leaks
    delete[] myArray[0];
    delete[] myArray;

    return 0;
}

