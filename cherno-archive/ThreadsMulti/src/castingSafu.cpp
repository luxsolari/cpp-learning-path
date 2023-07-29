#include "pch.h"

// Base case: combine hash of last argument with seed
template<typename T>
void hash_combine_impl(std::size_t& seed, const T& v)
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

// Recursive case: combine hash of current argument with hash of remaining arguments
template<typename T, typename... Args>
void hash_combine_impl(std::size_t& seed, const T& v, const Args&... args)
{
    hash_combine_impl(seed, args...);
    hash_combine_impl(seed, v);
}

// Wrapper function that calls hash_combine_impl with a seed value
template<typename... Args>
std::size_t hash_combine(const Args&... args)
{
    std::size_t seed = 0;
    hash_combine_impl(seed, args...);
    return seed;
}

struct Vector2
{
	float x, y;
};

class Entity
{
public:
	virtual void PrintName() { std::cout << "Entity" << std::endl; }
	virtual void PrintPosition() { std::cout << m_Position.x << ", " << m_Position.y << std::endl; }

	virtual ~Entity() = default; // virtual destructor to make sure the correct destructor is called when deleting a pointer to a derived class.

	// hash
	friend std::size_t hash_value(const Entity& e) {
		return hash_combine(e.m_Position.x, e.m_Position.y);
	}
protected:
	Vector2 m_Position;
};

class Player : public Entity
{
public:
	virtual void PrintName() override { std::cout << "Player" << std::endl; }
	void PrintGold() { std::cout << m_Gold << std::endl; }
	void PrintPlayerName() { std::cout << m_Name << std::endl; }

	// constructor with initializer list
	Player() : m_Name("Player"), m_Gold(100) {}
	// constructor with initializer list and parameters for them
	Player(const std::string& name, int gold) : m_Name(name), m_Gold(gold) {}

	// Copy constructor
	Player(const Player& other) : m_Name(other.m_Name), m_Gold(other.m_Gold) {}

	// Move constructor
	Player(Player&& other) noexcept : m_Name(std::move(other.m_Name)), m_Gold(other.m_Gold) {}

	// Operator overloads
	// Copy assignment operator
	Player& operator=(const Player& other)
	{
		m_Name = other.m_Name;
		m_Gold = other.m_Gold;
		return *this;
	}

	// Move assignment operator
	Player& operator=(Player&& other) noexcept
	{
		m_Name = std::move(other.m_Name);
		m_Gold = other.m_Gold;
		return *this;
	}

	// hash
	friend std::size_t hash_value(const Player& p) {
		return hash_combine(p.m_Name, p.m_Gold);
	}
private:
	std::string m_Name;
	int m_Gold;
};

class Enemy : public Entity
{
public:
	virtual void PrintName() override { std::cout << "Enemy" << std::endl; }
	void PrintHealth() { std::cout << m_Health << std::endl; }
	void PrintEnemyName() { std::cout << m_Name << std::endl; }
	void PrintGoldDrop() { std::cout << m_goldDrop << std::endl; }

	// constructor with initializer list and parameters for them
	Enemy(const std::string& name, int health, int goldDrop) : m_Name(name), m_Health(health), m_goldDrop(goldDrop) {
		std::cout << "Enemy constructor" << std::endl;
	}

	// Copy constructor
	Enemy(const Enemy& other) : m_Name(other.m_Name), m_Health(other.m_Health), m_goldDrop(other.m_goldDrop) {
		std::cout << "Enemy copy constructor" << std::endl;
		std::cout << "copy constructing " << m_Name << " with health " << m_Health << " and gold drop " << m_goldDrop << std::endl;

	}

	// Move constructor
	Enemy(Enemy&& other) noexcept : m_Name(std::move(other.m_Name)), m_Health(other.m_Health), m_goldDrop(other.m_goldDrop) {
		std::cout << "Enemy move constructor" << std::endl;
		std::cout << "move constructing " << m_Name << " with health " << m_Health << " and gold drop " << m_goldDrop << std::endl;

	}

	// Operator overloads
	// Copy assignment operator
	Enemy& operator=(const Enemy& other)
	{
		std::cout << "Enemy copy assignment operator" << std::endl;
		std::cout << "copy assigning " << m_Name << " with health " << m_Health << " and gold drop " << m_goldDrop << std::endl;

		m_Name = other.m_Name;
		m_Health = other.m_Health;
		m_goldDrop = other.m_goldDrop;
		return *this;
	}

	// Move assignment operator
	Enemy& operator=(Enemy&& other) noexcept
	{
		std::cout << "Enemy move assignment operator" << std::endl;
		std::cout << "move assigning " << m_Name << " with health " << m_Health << " and gold drop " << m_goldDrop << std::endl;

		m_Name = std::move(other.m_Name);
		m_Health = other.m_Health;
		m_goldDrop = other.m_goldDrop;
		return *this;
	}

	// equals operator
	bool operator==(const Enemy& other) const
	{
		return m_Name == other.m_Name && m_Health == other.m_Health && m_goldDrop == other.m_goldDrop;
	}

	// hash
	friend std::size_t hash_value(const Enemy& e) {
		return hash_combine(e.m_Name, e.m_Health, e.m_goldDrop);
	}

private:
	std::string m_Name;
	int m_Health;
	int m_goldDrop;
};


int main()
{
	// create an Entity pointer instance on the	heap. 
	Entity* e = new Entity();

	// create a copy of the Entity pointer instance. This is a shallow copy. 
	// This just copies the pointer. The pointer points to the same memory address as the original pointer.
	Entity* e2 = e;

	// create a copy of the Entity pointer instance. This is a deep copy. 
	// This creates a new instance of the Entity class and copies the values from the original pointer to the new pointer.
	Entity* e3 = new Entity(*e);

	// move the Entity pointer instance to a new pointer. This is a shallow copy. 
	//This just copies the pointer. The pointer points to the same memory address as the original pointer.
	Entity* e4 = std::move(e);

	// move the Entity pointer instance to a new pointer. This is a deep copy. 
	// This creates a new instance of the Entity class and copies the values from the original pointer to the new pointer.
	Entity* e5 = new Entity(std::move(*e3));

	// how many pointers do i have?
	std::cout << "e:  " << e << std::endl;
	std::cout << "e2: " << e2 << std::endl;
	std::cout << "e3: " << e3 << std::endl;
	std::cout << "e4: " << e4 << std::endl;
	std::cout << "e5: " << e5 << std::endl;
	std::cout << std::endl;

	// Create an Enemy pointer instance on the heap.
	Enemy* enemy = new Enemy("Enemy", 100, 10);
	std::cout << "enemy:  " << enemy << std::endl;
	std::cout << std::endl;

	// Create a copy of the Enemy pointer instance. This is a shallow copy.
	// This just copies the pointer. The pointer points to the same memory address as the original pointer.
	Enemy* enemy2 = enemy;
	std::cout << "enemy2: " << enemy2 << std::endl;
	std::cout << std::endl;

	// Create a copy of the Enemy pointer instance. This is a deep copy.
	// This creates a new instance of the Enemy class and copies the values from the original pointer to the new pointer.
	Enemy* enemy3 = new Enemy(*enemy);
	std::cout << "enemy3: " << enemy3 << std::endl;
	std::cout << std::endl;

	// move the Enemy pointer instance to a new pointer. This is a shallow copy.
	// This just copies the pointer. The pointer points to the same memory address as the original pointer.
	Enemy* enemy4 = std::move(enemy);
	std::cout << "enemy4: " << enemy4 << std::endl;
	std::cout << std::endl;

	// move the Enemy pointer instance to a new pointer. This is a deep copy.
	// This creates a new instance of the Enemy class and copies the values from the original pointer to the new pointer.
	Enemy* enemy5 = new Enemy(std::move(*enemy3));
	std::cout << "enemy5: " << enemy5 << std::endl;
	std::cout << std::endl;

	// how many pointers do i have?

	Entity player = Player("Player", 10); // create a Player instance on the stack and pass it to the Entity constructor
	player.PrintName(); // call the PrintName() function from the Entity class due to object slicing.
	// print size in bytes of player
	std::cout << "Size of player: " << sizeof(player) << std::endl;

	Player player2("Player2", 10); // create a Player instance on the stack
	Entity& player2Ref = player2; // create a reference to the Player instance
	player2Ref.PrintName(); // call the PrintName() function from the Player class due to polymorphism.
	// print size in bytes of player2Ref
	std::cout << "Size of player2: " << sizeof(player2) << std::endl;


	// create a vector of 4 players
	std::vector<Player> players = { Player("Player1", 10), Player("Player2", 10), Player("Player3", 10), Player("Player4", 10) };
	// create a vector of 4 enemies
	std::vector<Enemy> enemies = { Enemy("Enemy1", 10, 10), Enemy("Enemy2", 10, 10), Enemy("Enemy3", 10, 10), Enemy("Enemy4", 10, 10) };

	// create a data structure to hold both players and enemies
	std::vector<Entity*> entities;
	// add players to the entities vector
	for (auto& player : players)
	{
		entities.push_back(&player);
	}
	// add enemies to the entities vector
	for (auto& enemy : enemies)
	{
		entities.push_back(&enemy);
	}
	// shuffle them
	std::random_shuffle(entities.begin(), entities.end());

	// print out the details of the entities doing the appropriate casts
	for (auto& entity : entities)
	{
		// check if the entity is a player
		if (dynamic_cast<Player*>(entity))
		{
			// cast the entity to a player and print out the details
			Player* player = dynamic_cast<Player*>(entity);
			player->PrintPlayerName();
			std::cout << " with gold ";  player->PrintGold();
		}
		// check if the entity is an enemy
		else if (dynamic_cast<Enemy*>(entity))
		{
			// cast the entity to an enemy and print out the details
			Enemy* enemy = dynamic_cast<Enemy*>(entity);
			enemy->PrintEnemyName(); std::cout << " with health "; enemy->PrintHealth(); std::cout << " and gold drop "; enemy->PrintGoldDrop();
		}
	}

	std::cin.get();
}
