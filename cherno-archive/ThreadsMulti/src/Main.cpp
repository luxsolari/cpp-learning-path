#include "pch.h"
#include <chrono>
#include <thread>

static bool s_Finished = false;

struct Timer
{
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration{};
	Timer()
	{
		start = std::chrono::high_resolution_clock::now();
	}
	~Timer()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		float ms = duration.count() * 1000.0f;
		std::cout << "Timer took " << ms << "ms" << std::endl;
	}
};

void DoWork ()
{
	Timer timer;
	using namespace std::chrono_literals;
	std::cout << "Started thread id = " << std::this_thread::get_id() << std::endl;

	while (!s_Finished)
	{
		std::cout << "Working..." << std::endl;

		// sleep for 1 second (1000 milliseconds)
        std::this_thread::sleep_for(1s);
	}

	std::cout << "Finished thread id = " << std::this_thread::get_id() << std::endl;
}

int notmain ()
{

	std::cout << "Started thread id = " << std::this_thread::get_id() << std::endl;
	std::thread worker (DoWork);

	std::cin.get(); 
	s_Finished = true; 

	worker.join(); // wait for the thread to finish before exiting the program (otherwise the program will terminate before the thread has finished)

	std::cout << "Finished." << std::endl;


	std::cout << "Press enter to start measurement...";
	std::cin.get();

	auto start = std::chrono::high_resolution_clock::now();

	// sleep for 1 second
	std::this_thread::sleep_for(std::chrono::seconds(1));

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration = end - start;

	// print duration to console
	std::cout << "Duration: " << duration.count() << " seconds" << std::endl;

	std::cout << "Finished thread id = " << std::this_thread::get_id() << std::endl;
	return 0;
}

