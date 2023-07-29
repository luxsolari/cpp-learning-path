#include <iostream>
#define LOG(x) std::cout << std::dec << x << std::endl; // Print in decimal format.
#define LOG_HEX(x) std::cout << "0x" << std::hex << x << std::endl; // Print in hex format.

void Increment(int value);
void IncrementByRef(int& value);

int main()
{
	// Intro to pointers
	// Pointers are variables that store the address of another variable.
	// Pointers are used to access the memory address of another variable.

	int var = 8;

	void* ptr = 0; // This is the purest of pointers, because it is typeless. It is not valid because it is not pointing to anything. 
	ptr = &var; // ptr is now pointing to the address of var.

	int* ptr2 = &var; // ptr2 is now pointing to the address of var.
	*ptr2 = (int)10; // ptr2 is now pointing to the address of var, and the value of var is now 10.

	LOG(var);   // var is 10.
	LOG(*ptr2); // *ptr2 is the value of the address that ptr2 is pointing to.
	LOG_HEX(ptr2);  // ptr2 is the address of var.

	char* buffer = new char[8]; // This is a pointer to an array of 8 characters.
	memset(buffer, 0, 8); // This is a function that sets the first 8 bytes of the buffer to 0.

	char** ptr3 = &buffer; // This is a pointer to a pointer to a character.

	delete[] buffer; // This is a function that deletes the buffer. This is important because if you don't delete the buffer, you will have a memory leak.

	// A memory leak is when you allocate memory, but you don't delete it. This will cause your program to run slower and slower over time.
	// This is because the memory is not being freed up, and the program is using more and more memory.
	// This is why it is important to delete memory when you are done with it.	 

	// Intro to References
	// References are variables that are aliases of another variable.
	// References are used to pass variables by reference.

	int a = 5;
	int b = 8;
	int& ref = a; // ref is now an alias of a.

	ref = 2; // ref is now 2, and a is now 2.

	// References are useful because they are a way to pass variables by reference.
	// This is useful because it allows you to change the value of a variable in a function, without having to return the variable.

	Increment(a); // This will not change the value of a.
	IncrementByRef(a); // This will change the value of a.

	LOG(a); // a is now 3.
	LOG(ref); // ref is now 3.
	LOG(b); // b is now 8.

	ref = b; // the value of a will now be the same as the value of b.

	LOG(a); // a is now 8.
	LOG(ref); // ref is now 8.
	LOG(b); // b is now 8.

	return 0;
}

void Increment(int value)
{
	value++; // This will not change the value of the variable in the main function. 
	// This is because the value of the variable is being passed to the function, not the address of the variable.
	// This is called pass by value.
	// If you want to change the value of the variable in the main function, you need to pass the address of the variable to the function. 
}

void IncrementByRef(int& value)
{
	value++; // This will change the value of the variable in the main function.
	// This is because the address of the variable is being passed to the function, not the value of the variable.
	// This is called pass by reference.
}
