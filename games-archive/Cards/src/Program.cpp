#include <iostream>
#include "utils/io/Input.h"
#include "utils/factory/InputFactory.h"

int main ()
{
    std::cout << "Hello World!" << std::endl;

    {
        bool running = true;
        Input *input = InputFactory::createInput();

        while (running) {
            input->Update();

            if (input->IsKeyPressed('Q')) {
                running = false;
                std::cout << "Q pressed" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
        }
    }

    std::cout << "Goodbye World!" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    return 0;
}
