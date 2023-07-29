#pragma once
#include <iostream>
#include <string>
#include <vector>

struct Entity
{
	int x, y;
	
	Entity(float x, float y) : x(x), y(y){}

	// copy constructor
	Entity(const Entity& other) : x(other.x), y(other.y)
	{
		std::cout << "Copied Entity!" << std::endl;
	}

	// This is the operator<< overload for the Entity struct (friend function).
	// It is a friend function because it is not a member of the Entity struct.
	friend std::ostream& operator<<(std::ostream& stream, const Entity& entity)
	{
		stream << entity.x << ", " << entity.y;
		return stream;
	}
};

struct Item {
	std::string name;
	
	friend std::ostream& operator<<(std::ostream& stream, const Item& item) 
	{
		stream << item.name;
		return stream;
	}
};

struct Player : Entity
{
	std::string name;
	int health;
	std::vector<Item> inventory;

};

struct Enemy : Entity
{
	std::string name;
	int health;
};
