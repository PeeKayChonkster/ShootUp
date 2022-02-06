#include <iostream>
#include "app.hpp"
#include "prim_exception.hpp"

int main(int argc, char** argv)
{
    const uint16_t windowWidth = 800u;
    const uint16_t windowHeight = 800u;
    const char* windowTitle = "ShootUp";
    prim::App game(windowWidth, windowHeight, windowTitle);

    try
    {
        return game.run();
    }
    catch(const prim::Exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 1;
}