#include <iostream>
#include <string>
using String = std::string;

class Entity; // Forward declaration.
void PrintEntity(Entity* e);
void PrintEntity(const Entity* e);
void PrintEntityWithRef(const Entity& e);

class Entity
{
public:
	int x, y;

	Entity(int x, int y)
	{
		// Arrow operator.
		// The arrow operator is used to access the members of a class or struct through a pointer.
		// The this keyword is a pointer to the current object.
		Entity* const e = this; 

		// Dereference and access the members.
		(*this).x = x; 
		(*this).y = y;

		// The arrow operator is a shortcut for the above.
		this->x = x;
		this->y = y;

		PrintEntity(this); // Passing the current instance of the class. Here the type of this is Entity*.
		PrintEntityWithRef(*this); // Passing the current instance of the class. Here the type of this is Entity&.
	}
	
	int GetX() const {
		const Entity* const e = this;

		PrintEntity(this); // Passing the current instance of the class. Here the type of this is Entity*.
		PrintEntityWithRef(*this); // Passing the current instance of the class. Here the type of this is Entity&.
		
		return this->x;
	}

	void bizarreMehtod() {
		delete this; 
	}
};

void PrintEntity(Entity* e)
{
	std::cout << e->x << ", " << e->y << std::endl;
}

void PrintEntity(const Entity* e)
{
	std::cout << e->x << ", " << e->y << std::endl;
}

void PrintEntityWithRef(const Entity& e)
{
	std::cout << e.x << ", " << e.y << std::endl;
}

int main()
{
	Entity a = Entity(1, 2);
	a.GetX();
	a.bizarreMehtod(); 
}
