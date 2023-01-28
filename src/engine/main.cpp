#include "Engine.hpp"
#include <iostream>

int main()
{
    engine::Engine engine = engine::Engine::getEngine();
    engine.run();
    std::cout << "Hello world!" << std::endl;
}
