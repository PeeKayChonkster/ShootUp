#include <iostream>
#include <raylib-cpp.hpp>

int main(int argc, char** argv)
{
    const uint16_t windowWidth = 800u;
    const uint16_t windowHeight = 800u;
    const char* windowTitle = "ShootUp";
    raylib::Window window(windowWidth, windowHeight, windowTitle);

    window.SetTargetFPS(60);

    while(!window.ShouldClose())
    {
        window.BeginDrawing();

        window.ClearBackground();

        window.EndDrawing();
    }

    return 0;
}