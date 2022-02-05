#include <iostream>
#include <raylib-cpp.hpp>
#include "node2D.hpp"
#include "sprite.hpp"
#include "prim_exception.hpp"
#include "chonky_timer.hpp"

int main(int argc, char** argv)
{
    const uint16_t windowWidth = 800u;
    const uint16_t windowHeight = 800u;
    const char* windowTitle = "ShootUp";
    raylib::Window window(windowWidth, windowHeight, windowTitle);

    window.SetTargetFPS(60);
    float deltaTime = 0.0f;

    try
    {
        // TESTING //
        prim::Node2D testPlayer("testPlayer");
        prim::Sprite playerSprite("./res/textures/TestPlayer.png", "playerSprite");
        testPlayer.transform.addChild(&playerSprite);
        /////////////

        prim::Timer deltaTimer;
        deltaTimer.start();

        while(!window.ShouldClose())
        {
            deltaTime = deltaTimer.peekSinceLastPeek();

            // LOGIC HERE //
            if(IsKeyDown(KEY_D)) testPlayer.transform.move(raylib::Vector2::Right());
            if(IsKeyDown(KEY_S)) testPlayer.transform.move(raylib::Vector2::Up());
            if(IsKeyDown(KEY_A)) testPlayer.transform.move(raylib::Vector2::Left());
            if(IsKeyDown(KEY_W)) testPlayer.transform.move(raylib::Vector2::Down());

            if(IsKeyDown(KEY_Q)) testPlayer.transform.rotate(1.0f);
            if(IsKeyDown(KEY_E)) testPlayer.transform.rotate(-1.0f);

            if(IsKeyDown(KEY_U)) testPlayer.transform.scaleUp(raylib::Vector2::Up() * 0.1f);
            if(IsKeyDown(KEY_J)) testPlayer.transform.scaleUp(raylib::Vector2::Down() * 0.1f);
            if(IsKeyDown(KEY_I)) testPlayer.transform.scaleUp(raylib::Vector2::Right() * 0.1f);
            if(IsKeyDown(KEY_Y)) testPlayer.transform.scaleUp(raylib::Vector2::Left() * 0.1f);


            ////////////////

            window.BeginDrawing();

            window.ClearBackground();

            // DRAW HERE //
            testPlayer.draw();
            ///////////////

            window.EndDrawing();
        }

    }
    catch(const prim::Exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}