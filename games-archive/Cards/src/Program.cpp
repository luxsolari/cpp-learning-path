#include "utils/io/Input.h"
#include "utils/factory/InputFactory.h"
#include "utils/factory/OutputFactory.h"
#include "utils/io/Output.h"

int main ()
{
    bool   running = true;
    Input*   input = InputFactory::createInput();
    Output* output = OutputFactory::createOutput();

    input->Start();

    while (running) {
        if (input->IsKeyPressed('Q')) {
            running = false;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    return 0;
}
