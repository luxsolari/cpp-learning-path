// Static keyword has two meanings in C++.
// 1. It is used to declare a variable as static. This means that the variable is only linked inside the file that it is declared in.
// 2. When used inside a class or a struct it means that the variable is shared by all instances of the class or struct.
//
// Static variables are useful because they are only linked inside the file that they are declared in.
// This means that if you have two files that both have a static variable with the same name, they will not conflict with each other.
// This is useful when you have a header file that is included in multiple files.
// If you have a static variable inside the header file, it will only be linked once inside the file that includes the header file.

// In classes and structs, static variables are shared by all instances of the class or struct.
// This means that if you have a static variable inside a class, it will be shared by all instances of the class.
// This is useful when you have a variable that you want to be shared by all instances of the class.


static int s_Variable = 5; // It is initialized to 5. It is static so it will be only linked inside this file.
int ss_Variable = 5; // It is initialized to 5. It is not static so it will be linked inside all files that include this header file.

static void Function() {
	// Local static variables are only initialized once.
	// This means that if you call this function multiple times, the local static variable will only be initialized once.
	static int s_Variable = 5;

}

// static keyword has two meanings in C++.
// 1. It is used to declare a variable as static. This means that the variable is only linked inside the file that it is declared in.
// 2. When used inside a class or a struct it means that the variable is shared by all instances of the class or struct.
// A static class is a class that can only have static members. This means that it can only have static variables and static functions.
// Static classes are linked inside the file that they are declared in. 
// This means that if you have two files that both have a static class with the same name, they will not conflict with each other.
static class Logger
{
public:
	static void Log(const char* message)
	{
		// This is a static function. This means that it can only access static variables.
	}
};
