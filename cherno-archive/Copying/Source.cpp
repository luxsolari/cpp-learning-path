#include <iostream>
#include <vector>
#include <string>

struct Vector2
{
	float x, y;
};

class String
{
private:
	char* m_Buffer;
	unsigned int m_Size;
public:
	String(const char* string)
	{
		m_Size = strlen(string);
		m_Buffer = new char[m_Size + 1];
		memcpy(m_Buffer, string, m_Size);
		m_Buffer[m_Size] = 0;
	}
	
	String(const String& other) // This is a copy constructor. It is called when you pass an object by value. It is also called when you return an object by value.
		: m_Size(other.m_Size)
	{
		std::cout << "Copied string!" << std::endl;
		m_Buffer = new char[m_Size + 1];
		memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
	}

	~String()
	{
		delete[] m_Buffer;
	}

	char& operator[](unsigned int index)
	{
		return m_Buffer[index];
	}

	friend std::ostream& operator<<(std::ostream& stream, const String& string);
};

std::ostream& operator<<(std::ostream& stream, const String& string)
{
	stream << string.m_Buffer;
	return stream;
}

void PrintString(const String& string)
{
	std::cout << string << std::endl;
}

int main()
{
	int a = 2;
	int b = a;

	Vector2 v1 = { 1.0f, 2.0f };
	Vector2 v2 = v1;

	Vector2* v1h = new Vector2{ 1.0f, 2.0f };
	Vector2* v2h = v1h; // This is a shallow copy. It copies the pointer, not the data.
	
	String string = "Cherno";
	String second = string; // Copy constructor is called here. This is a deep copy.

	string[2] = 'a';

	String& someRef = string; // This is a reference. It is not a copy. It is just an alias.
	someRef[2] = 'e'; // This will change the string. This is because the reference is just an alias.
	
	PrintString(string);
	PrintString(second);

	std::cin.get();
}
