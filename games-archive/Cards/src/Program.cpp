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
    output->Start();

    while (running) {
        if (input->IsKeyPressed('Q') || input->IsKeyPressed('q')) {
            running = false;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    input->Stop();
    output->Stop();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    return 0;
}
