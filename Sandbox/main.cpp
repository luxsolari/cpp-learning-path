#include <iostream>

// The book "Effective C++" is a good reference, as it recommends using inlines, enums and consts instead of macros.
// Macros are not type safe, and they can be dangerous. They are also not scoped, so they can be used anywhere in the program.
// They are also not debuggable, as they are expanded at compile time, and not at runtime.
// Macros are also not portable, as they are expanded by the compiler, and not the preprocessor. This means that the compiler
// may use different macros for different platforms, or even different versions of the same platform.

#define PRINT(x) std::cout << x << std::endl // this is a macro definition (not a function).
											 // It is a preprocessor directive, and it will be expanded by the compiler at compile time 
											 // before the program is compiled.
											 // Instead of this, we should use a function, as it is type safe, and scoped.

#define MY_MAGIC_CONSTANT = 42				 // this is a macro definition of a constant. It will be replaced by the compiler with the value 42.
											 // Instead of this, we should use constants, as they are type safe, and scoped. 
const int MyMagicConstant = 42;				 // this is a constant declaration instead of a macro definition.

// Here is a way of re-implementing the PRINT macro as a function:
void print(const char* str, int length = 0) // the default length is 0. Optional parameters.
{
	// if length is not specified, calculate it:
	if (length == 0)
	{
		length = static_cast<int>(strlen(str));
	}

	for (int i = 0; i < length; i++)
	{
		std::cout << str[i];
	}
	std::cout << std::endl;
}

int main()
{
	const char* str = "Hello World!";		 // this is a constant string in C-style. 
	int len = static_cast<int>(strlen(str)); // get the length of the string above.

	print("Hello World!", len); 
	
	return 0;

}

class Entity {
	int m_X, m_Y;

	const int const getPositionX() const {
		return m_X;
	}
	const int const getPositionY() const {
		return m_Y;
	}
public:

	Entity(int m_X, int m_Y)
		: m_X(m_X), m_Y(m_Y)
	{
	}

	Entity() = default;

	bool operator==(const Entity& other) const
	{
		return m_X == other.m_X && m_Y == other.m_Y;
	}

	const Entity getMyself() 
	{
		return *this;
	}
};
