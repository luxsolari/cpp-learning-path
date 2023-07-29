#include <iostream>
#define LOG(x) std::cout << std::dec << x << std::endl; // Print in decimal format.
#define LOG_HEX(x) std::cout << "0x" << std::hex << x << std::endl; // Print in hex format.
#define LOG_BIN(x) std::cout << "0b" << std::bitset<8>(x) << std::endl; // Print in binary format.

// Intro to Classes
// Classes are a way to group variables and functions together.
// Classes are a way to create custom data types.
// Classes are a way to create objects.

class Player {
private:
	int x, y;
	int speed;

public:	
	void Move(int xa, int ya) {
		x += xa * speed;
		y += ya * speed;
	}
	
	void setSpeed(int speed) {
		this->speed = speed;
	}

	void setX(int x) {
		if (x < 0) {
			this->x = 0;
		}
		else {
			this->x = x;
		}
	}
	
	void setY(int y) {
		if (y < 0) {
			this->y = 0;
		}
		else {
			this->y = y;
		}
	}
};

// Difference between a class and a struct.
// A struct is a class where all the variables are public by default.
// A class is a class where all the variables are private by default.

// You can make a class public by default by using the keyword public before the class name.
// You can make a struct private by default by using the keyword private before the struct name.


int main()
{
	Player player{}; // Create an instance of the Player class. This is called an object. This is initialized on the stack.
	Player player2 = Player(); // This is the same as the line above. This is also initialized on the stack.
	
	Player* player3 = new Player(); // This is initialized on the heap. This is not recommended because it is slower.
	
	// Variables made from class types are called objects. 
	// Objects are instances of classes.
	
	// Accessing the variables of the object. These are called fields. These fields are public so we can access them directly.
	player.setX(5);
	player.setY(3);
	player.setSpeed(2);
	
	player.Move(1, -1);
	 
	return 0;
}

