#include "app.hpp"
#include "prim_exception.hpp"
#include "chonky_timer.hpp"
#include "sprite.hpp"
#include <memory>
#include <iostream>
#include "debug.hpp"
#include <algorithm>
#include "node_library.hpp"

prim::App::App(uint16_t windowWidth, uint16_t windowHeight, std::string windowName): window(windowWidth, windowHeight, windowName) 
{
    root = createNode("root");
}

prim::App::~App()
{
    for(int i = 0; i < nodes.size(); ++i)
    {
        std::cout << "Deleted node: " << nodes[i]->name << "; ID: " << nodes[i]->getId() << std::endl;
        delete nodes[i];
    }
}

void prim::App::deleteNode(Node2D* node)
{
    deleteNodeChildren(node);
    std::cout << "Deleted node: " << node->name << std::endl;
    auto iter = std::find_if(nodes.begin(), nodes.end(), [&] (const Node2D* n) { return n->getId() == node->getId(); });
    if(iter != nodes.end()) nodes.erase(iter);
    delete node;
}

// Helper function for recursion
void prim::App::deleteNodeChildren(prim::Node2D* node)
{
    for(int i = 0; i < node->transform.children.size(); ++i)
    {
        deleteNodeChildren(node->transform.children[i]->node);
        std::cout << "Deleted node: " << node->transform.children[i]->node->name << std::endl;
        delete node->transform.children[i]->node;
    }
}

int prim::App::init()
{
    window.SetTargetFPS(60);

    // TESTING //
    Node2D* player = createNode<Node2D>("player");
    Sprite* playerSprite = createNode<Sprite>("playerSprite", "/home/prim/Projects/C++/ShootUp/project/res/textures/player/ManWalkRightSheet.png", 10u, 1u);
    InputController* playerController = createNode<InputController>("playerController", player);
    AnimationPlayer* playerAnimationPlayer = createNode<AnimationPlayer>("animationPlayer");
    Animation* anim = playerAnimationPlayer->createAnimation("playerWalk", 1000.0f, 10u);
    anim->createStrip(&(playerSprite->hframe), 0u);
    playerAnimationPlayer->play("playerWalk");


    player->transform.addChild(playerSprite);
    player->transform.addChild(playerController);
    player->transform.addChild(playerAnimationPlayer);
    root->transform.addChild(player);
    /////////////

    return 0;
}

int prim::App::run()
{
    if(init() != 0) throw PRIM_EXCEPTION("prim::App couldn't initialize.");
    prim::Timer deltaTimer;
    deltaTimer.start();
    while(!window.ShouldClose())
    {
        deltaTime = deltaTimer.peekSinceLastPeek();

        root->update(deltaTime);

        window.BeginDrawing();

        window.ClearBackground();
        root->draw();
        Debug::draw();

        window.EndDrawing();
    }

    deltaTimer.reset();
    return 0;
}