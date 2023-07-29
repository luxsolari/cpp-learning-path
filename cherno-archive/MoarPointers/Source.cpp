#include <iostream>
using String = std::string;

int main()
{
	// Smart pointers
	// They are wrappers around pointers that provide additional functionality.
	// 1. Unique pointer
	// 2. Shared pointer
	// 3. Weak pointer
	// They are used to manage memory in a safe way and avoid memory leaks.
	
	// Unique pointer
	// It is a smart pointer that owns and manages another object through a pointer and disposes of that object when the unique pointer goes out of scope.
	// It can only point to one object at a time.

	// Unique pointer example
	std::unique_ptr<int> uniquePtr = std::make_unique<int>(5);		// Unique pointer declaration and initialization
	*uniquePtr = 10;												// Unique pointer dereference and assignment
	std::cout << *uniquePtr << std::endl;							// Unique pointer access
	
	// Shared pointer
	// It is a smart pointer that retains shared ownership of an object through a pointer. Several shared pointers may own the same object.
	// When the last remaining shared pointer to an object is destroyed or goes out of scope, the object of that shared pointer is destroyed.
	
	// Shared pointer example
	std::shared_ptr<int> sharedPtr = std::make_shared<int>(5);		// Shared pointer declaration and initialization
	*sharedPtr = 10;												// Shared pointer dereference and assignment
	std::cout << *sharedPtr << std::endl;							// Shared pointer access
	
	// Weak pointer
	// It is a smart pointer that holds a non-owning ("weak") reference to an object that is managed by std::shared_ptr. 
	// It must be converted to std::shared_ptr in order to access the referenced object.
	
	// Weak pointer example
	std::weak_ptr<int> weakPtr = sharedPtr;							// Weak pointer declaration and initialization
	std::cout << *weakPtr.lock() << std::endl;						// Weak pointer access
	*weakPtr.lock() = 999;										    // Weak pointer conversion to shared pointer
	weakPtr.reset();												// Weak pointer reset
	
	std::cin.get();
}
