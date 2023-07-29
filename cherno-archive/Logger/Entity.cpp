#include <iostream>
#include <string>
#include <stdlib.h>
// Inheritance
// Inheritance is a way to create a class that inherits from another class.
// The class that inherits is called a derived class and the class that is inherited from is called a base class.
// The derived class inherits all the public and protected members of the base class.
// The derived class can add new members to the base class.

class Printable {
public:
	virtual std::string GetClassName() const = 0; // This is a pure virtual function. It is a function that has no body and must be overridden in the derived class.
	// This is useful for creating an interface.
	// An interface is a class that only has pure virtual functions.
	// This is useful for creating a base class that can be used as a type.
	// For example, if you have a function that takes a Printable object, you can pass in any derived class of Printable.
};

class Entity : public Printable { // This is a class. It is a way to create a custom data type that can have variables and functions.
public:
	float x = 0, y = 0;
	float speed = 1;

	void Move(float xa, float ya) {
		x += xa * speed;
		y += ya * speed;
	}	

	std::string GetName() { return "Entity"; }

	std::string GetClassName() const override {
		return "Entity";
	}
};

class Item : public Printable {
public:
	enum Class : unsigned short {
		CLASS_WEAPON = 0, CLASS_ARMOR, CLASS_CONSUMABLE, CLASS_QUEST, CLASS_MISC, CLASS_NONE, CLASS_DEFAULT = CLASS_NONE
	};
private:
	std::string m_name;
	Class m_itemClass = Class::CLASS_DEFAULT;
public:
	Item(const std::string& name) : m_name(name) {}
	Item(const std::string& name, Class itemClass) : m_name(name) {
		m_itemClass = itemClass;
	}
	virtual std::string GetClassName() const override { return m_name; }
};

class Player : public Entity { // This is a class that inherits from Entity.
private:
	std::string m_name;
	int m_max_health;
	Item* items[10] = { new Item("Sword"), new Item("Shield"), new Item("Bow"), new Item("Arrow") };
	mutable int m_count = 0; // This is a mutable variable. It can be modified even if the object is a constant object.

public:
	Player(const std::string& name) : m_name(name) {}  // This is a constructor with an initializer list.
	explicit Player(const int max_health) : m_max_health(max_health) {} // This is a constructor with an initializer list. It is explicit so it cannot be used for implicit conversion.
	
	const Item* const GetItem(int index) const 
	{ 
		return items[index]; 
	}
	void SetItem(int index, Item* item) { items[index] = item; }

	const std::string& GetName() const {
		m_count++;	// This is a mutable variable. It can be modified even if the object is a constant object.
					// This allows const methods to modify this variable.
		return m_name; 
	}
	virtual std::string GetClassName() const override { return "Player"; }

	~Player() { // This is a destructor. It is called when the object is destroyed.
		for (int i = 0; i < 10; i++) {
			delete items[i];
		}
	}
};

struct Vector2 {
	float x, y;
	
	Vector2(float x, float y) : x(x), y(y) {}
	
	Vector2 Add(const Vector2& other) const {
		return Vector2(x + other.x, y + other.y);
	}
	
	Vector2 operator + (const Vector2& other) const { // This is an operator overload. It is a way to overload operators for custom classes.
		return Add(other);
	}

	Vector2 Multiply(const Vector2& other) const {
		return Vector2(x * other.x, y * other.y);
	}
	
	Vector2 operator * (const Vector2& other) const {
		return Multiply(other);
	}
	 
	bool operator == (const Vector2& other) const { 
		return x == other.x && y == other.y;
	}

	bool operator != (const Vector2& other) const {
		return !(*this == other); // This is a way to call another operator overload.
	}
};

std::ostream& operator << (std::ostream& stream, const Vector2& other) {
	stream << other.x << ", " << other.y;
	return stream;
}

void PrintName(const Printable* object) {
	std::cout << object->GetClassName() << std::endl;
}
 
// This is a function that takes a void pointer and an integer.
// It is a generic function that can increase any type of variable.
// This a demosntration of how to use void pointers. They are very flexible but not type safe. So proper caution should be taken when using them.
void Increase(void* data, int psize) { 
	
	if (psize == sizeof(char)) {
		char* pchar;
		pchar = (char*)data;
		++(*pchar);
	}
	else if (psize == sizeof(int)) {
		int* pint;
		pint = (int*)data;
		++(*pint);
	}
}


int main()
{
	Player ps = Player(200); // This is an example of implicit conversion. It is converting an integer to a Player object.
	
	int a = 10;
	int* b = &a; // This is a pointer. It is a variable that stores the address of another variable.
	int c = *b; // This is dereferencing. It is getting the value of the variable that the pointer is pointing to.
	int** d = &b; // This is a pointer to a pointer. It is a variable that stores the address of another pointer.

	void* e = &a; // This is a void pointer. It is a pointer that can point to any type of variable.
	// This is useful for creating a generic pointer that can point to any type of variable.

	int f = *(int*)e; // This is casting. It is converting a variable from one type to another.
	// This is useful for converting a void pointer to a specific type of pointer.
	// This is not recommended because it is not type safe.
	// It is better to use a static_cast.

	int g = *(static_cast<int*>(e)); // This is a static cast. It is converting a variable from one type to another.
	// This is useful for converting a void pointer to a specific type of pointer.
	// This is type safe.
	// It is better to use a static_cast.

	const Player p = Player("Player"); // This is a constant object. It is an object that cannot be modified.
	p.GetName();

    // print variables and addresses from line 97 through 110
	std::cout << "a: " << a << " " << &a << std::endl;
	std::cout << "b: " << b << " " << &b << " " << *b << std::endl;
	std::cout << "c: " << c << std::endl;
	std::cout << "d: " << d << " " << &d << " " << *d << " " << **d << std::endl;
	std::cout << "e: " << e << " " << &e << " " << *(int*)e << std::endl;
	std::cout << "f: " << f << std::endl;
	std::cout << "g: " << g << std::endl;

	// increase a by 1
	Increase(&a, sizeof(a));
	std::cout << "a: " << a << std::endl;
	// print variables again
	std::cout << "b: " << b << " " << &b << " " << *b << std::endl;
	std::cout << "c: " << c << std::endl;
	std::cout << "d: " << d << " " << &d << " " << *d << " " << **d << std::endl;
	std::cout << "e: " << e << " " << &e << " " << *(int*)e << std::endl;
	std::cout << "f: " << f << std::endl;
	std::cout << "g: " << g << std::endl;

	// Create a list of pointers to entities, initialize it with a player and an entity.
	Printable* entities[2];
	entities[0] = new Entity();
	entities[1] = new Player("Cherno");


	// Loop through the list and print the name of each entity.
	for (int i = 0; i < 2; i++) {
		PrintName(entities[i]);
	}

	// add potion item to player
	Player* const player = (Player*) entities[1];
	player->SetItem(4, new Item("Potion"));

	// print inventory of player
	// add title message
	std::cout << "Inventory of " << player->GetName() << std::endl;
	for (int i = 0; i < 5; i++) {
		PrintName(player->GetItem(i));
	}

	// access player like an entity
	Entity* entity = (Entity*)entities[1];
	std::cout << entity->GetName() << std::endl;

	// delete everything
	for (int i = 0; i < 2; i++) {
		delete entities[i];
	}

	char name[] = "Cherno"; // This is a string literal. It is a string that is stored in the executable. It is not stored in the heap.
	std::cout << name << std::endl; // This prints the string literal.
	name[0] = 'P'; // This changes the first character of the string literal to a 'P'. This is not recommended. It is better to use a std::string.
	std::cout << name << std::endl;

	const char* name2 = (char*)"hello"; // This is a string literal. It is a string that is stored in the executable. It is not stored in the heap.
	std::cout << name2 << std::endl;
	// name2[1] = 'o'; // this is not allowed because it is a string literal. It is stored in the executable and cannot be changed.

	std::string name3 = "Cherno";
	name3 += " Hello";
	bool contains = name3.find("Hello") != std::string::npos; // This checks if the string contains the substring "Hello".
	std::cout << contains << std::endl;
	contains = name3.find("Hi") != std::string::npos; // This checks if the string contains the substring "Hello".
	std::cout << contains << std::endl;

	const char luxSolari[11] = "Lux\0Solari";

	std::cout << strlen(luxSolari) << std::endl; // This prints the length of the string. It does not include the null terminator. It prints 3. It should print 10.
	// This is because the first null terminator is not counted. And the strlen function stops counting when it reaches the null terminator.

	std::cout << sizeof(luxSolari) << std::endl; // This prints the size of the array. It includes the null terminator. It prints 11.

	const char* anotherName = "Lux Solari";
	const wchar_t* anotherName2 = L"Cherno"; // This is a wide string literal.    It is a string literal that can store unicode characters. This is introduced in C++11.
	const char16_t* anotherName3 = u"Cherno"; // This is a unicode string literal. It is a string literal that can store unicode characters. This is introduced in C++11.
	const char32_t* anotherName4 = U"Cherno"; // This is a unicode string literal. It is a string literal that can store unicode characters. This is introduced in C++11.

	using namespace std::string_literals;  // C++14 feature. This allows you to use string literals without having to add the "s" at the end of the string.
	std::string name4 = "Cherno"s + "Hello"; // C++14 introduced the ability to concatenate string literals.
	name4 += "Hello"s + "asd"s; // C++14 introduced the ability to concatenate string literals.


	const char* name5 = R"(
	Cherno, asd asd ad
	asdasdasd asd asdd
	asdasdasdasdasdasd)"; // Raw strings in C++14 allow writing strings with special characters like multiple lines.
	std::cout << name5 << std::endl;

	// Print type sizes
	std::cout << "Size of char: " << sizeof(char) << std::endl;
	std::cout << "Size of wchar_t: " << sizeof(wchar_t) << std::endl;
	std::cout << "Size of char16_t: " << sizeof(char16_t) << std::endl;
	std::cout << "Size of char32_t: " << sizeof(char32_t) << std::endl;
	std::cout << "Size of int: " << sizeof(int) << std::endl;
	std::cout << "Size of short: " << sizeof(short) << std::endl;
	std::cout << "Size of long: " << sizeof(long) << std::endl;
	std::cout << "Size of long long: " << sizeof(long long) << std::endl;
	std::cout << "Size of float: " << sizeof(float) << std::endl;
	std::cout << "Size of double: " << sizeof(double) << std::endl;
	std::cout << "Size of long double: " << sizeof(long double) << std::endl;
	std::cout << "Size of bool: " << sizeof(bool) << std::endl;
	std::cout << "Size of void*: " << sizeof(void*) << std::endl;

	// use a char variable as a flag array
	char flags = 0;
	flags |= 1 << 0; // set the first bit to 1
	flags |= 1 << 2; // set the third bit to 1

	for (int i = 0; i < 8; i++) {
		std::cout << ((flags & (1 << i)) ? 1 : 0);
	}
	std::cout << std::endl;
	// print all flag values
	for (int i = 0; i < 8; i++) {
		if (flags & (1 << i)) {
			std::cout << "Bit " << i << " is set!" << std::endl;
		}
	}
	
	const int MAX_ENTITIES = 100;
	
	// order of const matters when declaring a pointer.
	//
	
	const int* v1		= new int{MAX_ENTITIES}; // This is a pointer to a constant integer. The integer cannot be changed. The pointer can be changed.
	int const* v2		= new int{ MAX_ENTITIES }; // This is a pointer to a constant integer. The integer cannot be changed. The pointer can be changed. This is the same as the previous line.
	
	int* const v3	    = new int{ MAX_ENTITIES }; // This is a constant pointer to an integer. The integer can be changed. The pointer cannot be changed.
	
	int const* const v4 = new int{ MAX_ENTITIES }; // This is a constant pointer to a constant integer. The integer cannot be changed. The pointer cannot be changed.
	const int* const v5 = new int{ MAX_ENTITIES }; // This is a constant pointer to a constant integer. The integer cannot be changed. The pointer cannot be changed.
	
	auto func = [=]() mutable // This allows you to change the variables inside the lambda function. This is only allowed if the lambda function is mutable.
	{
		// *(v1) = 2; // This is not allowed because v1 is a pointer to a constant integer. The integer cannot be changed.
		v1 = &MAX_ENTITIES; // This is allowed because v1 is a pointer to a constant integer. The pointer can be changed.
		std::cout << v1 << " " << *v1 << std::endl;
		
		//*(v2) = 2; // This is not allowed because v2 is a pointer to a constant integer. The integer cannot be changed.
		v2 = &MAX_ENTITIES; // This is allowed because v2 is a pointer to a constant integer. The pointer can be changed.
		std::cout << v2 << " " << *v2 << std::endl;

		*(v3) = 2; // This is allowed because v3 is a constant pointer to an integer. The integer can be changed.
		//v3 = &MAX_ENTITIES; // This is not allowed because v3 is a constant pointer to an integer. The pointer cannot be changed.
		std::cout << v3 << " " << *v3 << std::endl;
		
		//*(v4) = 2; // This is not allowed because v4 is a constant pointer to a constant integer. The integer cannot be changed.
		//v4 = &MAX_ENTITIES; // This is not allowed because v4 is a constant pointer to a constant integer. The pointer cannot be changed.
		std::cout << v4 << " " << *v4 << std::endl;
	};

	func(); 

	int s_Level = 10;
	// Nested ternary operator example.
	std::string rank = s_Level > 15 ? "Master" :
					   s_Level > 10 ? "Intermediate":
					   s_Level > 5  ? "Beginner" : 
									  "Noob"; 

	//char* p3 = (char*)"Lux Solari"; // This is a bad way of doing this. This is a const cast. This is not allowed in C++.
	//*p3 = 'k';
	
	Vector2 vec1(1.0f, 2.0f);
	Vector2 vec2(3.0f, 4.0f);
	
	Vector2 vec3 = vec1 + vec2;
	std::cout << vec3 << std::endl;
}

