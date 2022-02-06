#include "node_library.hpp"

/// InputController ///

prim::InputController::InputController(std::string name, Node2D* target): Node2D(name), target(target) {}

void prim::InputController::update(float deltaTime)
{
    UPDATE_OVERRIDE

    if(IsKeyDown(KEY_D)) target->transform.move({ 1.0f, 0.0f});
    if(IsKeyDown(KEY_S)) target->transform.move({ 0.0f, 1.0f});
    if(IsKeyDown(KEY_A)) target->transform.move({ -1.0f, 0.0f});
    if(IsKeyDown(KEY_W)) target->transform.move({ 0.0f, -1.0f});
    if(IsKeyDown(KEY_Q)) target->transform.rotate(1.0f);
    if(IsKeyDown(KEY_E)) target->transform.rotate(-1.0f);
}

///////////////////////