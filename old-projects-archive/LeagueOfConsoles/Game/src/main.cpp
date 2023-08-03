#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

struct AllocationMetrics {
	uint32_t TotalAllocated = 0;
	uint32_t TotalFreed = 0;

	uint32_t CurrentUsage() const { return TotalAllocated - TotalFreed; }
};

static AllocationMetrics g_AllocationMetrics;

void* operator new(size_t size)
{
	g_AllocationMetrics.TotalAllocated += size;
	std::cout << "Allocating " << size << " bytes" << std::endl;
	return malloc(size);
}

void operator delete(void* ptr, size_t size)
{
	g_AllocationMetrics.TotalFreed += size;
	std::cout << "Freeing " << size << " bytes" << std::endl;
	free(ptr);
}

struct Object {
	int x, y, z;
};

static void PrintMemoryUsage() {
	std::cout << "Current memory usage: " << g_AllocationMetrics.CurrentUsage() << " bytes" << std::endl;
}

int main()
{
	//sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);

	//while (window.isOpen())
	//{
	//    sf::Event event;
	//    while (window.pollEvent(event))
	//    {
	//        if (event.type == sf::Event::Closed)
	//            window.close();
	//    }

	//    window.clear();
	//    window.draw(shape);
	//    window.display();
	//}

	PrintMemoryUsage();
	std::string string = "A sample string";
	PrintMemoryUsage();

	Object* obj = new Object;
	PrintMemoryUsage();
	{
		std::unique_ptr<Object> obj2 = std::make_unique<Object>();
		PrintMemoryUsage();
	}
	PrintMemoryUsage();
	
	std::cin.get();
	return 0;
}
