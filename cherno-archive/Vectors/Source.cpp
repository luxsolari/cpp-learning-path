#include "Structures.h" // This is the file that contains the operator<< overload

int main()
{
	// Optimization of vectors demonstration (reserve() function)

	std::vector<Entity> entities; // This is a vector of Entity structs.
	entities.reserve(3);		  // optimizing the vector by reserving 3 spaces in memory.

	entities.emplace_back(1, 2);  // emplace_back is a function that constructs an object in place.
	entities.emplace_back(3, 4);
	entities.emplace_back(5, 6);


	std::cin.get();
}
