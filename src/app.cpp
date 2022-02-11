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

void prim::App::deleteNode(Node* node)
{
    deleteNodeChildren(node);
    std::cout << "Deleted node: " << node->name << std::endl;
    auto iter = std::find_if(nodes.begin(), nodes.end(), [&] (const Node* n) { return n->getId() == node->getId(); });
    if(iter != nodes.end()) nodes.erase(iter);
    delete node;
}

// Helper function for recursion
void prim::App::deleteNodeChildren(prim::Node* node)
{
    for(int i = 0; i < node->children.size(); ++i)
    {
        deleteNodeChildren(node->children[i]);
        std::cout << "Deleted node: " << node->children[i]->name << std::endl;
        delete node->children[i];
    }
}

int prim::App::init()
{
    window.SetTargetFPS(60);

    

    // TESTING //
    Node2D* player = createNode<Node2D>("player");
    Sprite* playerSprite = createNode<Sprite>("playerSprite", "/home/prim/Projects/C++/ShootUp/project/res/textures/player/idle/ManIdle.png", 1u, 1u);
    InputController* playerController = createNode<InputController>("playerController", player);
    AnimationPlayer* playerAnimationPlayer = createNode<AnimationPlayer>("animationPlayer");

    SpriteAnimation* animIdle = playerAnimationPlayer->createAnimation("idle", 10000.0f, playerSprite);
    animIdle->pushImage("/home/prim/Projects/C++/ShootUp/project/res/textures/player/idle/ManIdle.png");

    SpriteAnimation* animWalk = playerAnimationPlayer->createAnimation("walk", 1000.0f, playerSprite);
    animWalk->pushImage("/home/prim/Projects/C++/ShootUp/project/res/textures/player/walk/ManWalkRight1.png");
    animWalk->pushImage("/home/prim/Projects/C++/ShootUp/project/res/textures/player/walk/ManWalkRight2.png");
    animWalk->pushImage("/home/prim/Projects/C++/ShootUp/project/res/textures/player/walk/ManWalkRight3.png");
    animWalk->pushImage("/home/prim/Projects/C++/ShootUp/project/res/textures/player/walk/ManWalkRight4.png");
    animWalk->pushImage("/home/prim/Projects/C++/ShootUp/project/res/textures/player/walk/ManWalkRight5.png");
    animWalk->pushImage("/home/prim/Projects/C++/ShootUp/project/res/textures/player/walk/ManWalkRight6.png");
    animWalk->pushImage("/home/prim/Projects/C++/ShootUp/project/res/textures/player/walk/ManWalkRight7.png");
    animWalk->pushImage("/home/prim/Projects/C++/ShootUp/project/res/textures/player/walk/ManWalkRight8.png");
    animWalk->pushImage("/home/prim/Projects/C++/ShootUp/project/res/textures/player/walk/ManWalkRight9.png");
    animWalk->pushImage("/home/prim/Projects/C++/ShootUp/project/res/textures/player/walk/ManWalkRight10.png");

    player->addChild(playerSprite);
    player->addChild(playerController);
    player->addChild(playerAnimationPlayer);
    player->transform.move(raylib::Vector2(500.0f, 500.0f));
    root->addChild(player);
    /////////////

    // Start all nodes
    root->start();

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
    Resman::free();
    return 0;
}