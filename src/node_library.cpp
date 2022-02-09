#include "node_library.hpp"
#include <algorithm>
#include <iostream>

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

/// AnimationPlayer ///

prim::AnimationPlayer::AnimationPlayer(std::string name): Node2D(name) {}

prim::AnimationPlayer::~AnimationPlayer()
{
    for(int i = 0; i < animations.size(); ++i)
    {
        delete animations[i];
    }
}

prim::Animation* prim::AnimationPlayer::createAnimation(std::string name, float length, uint16_t frameCount)
{
    Animation* anim = new Animation(name, length, frameCount);
    pushAnimation(anim);
    return anim;
}


void prim::AnimationPlayer::pushAnimation(Animation* anim)
{
    // If animation isn't already exists in the vector
    if(std::find_if(animations.begin(), animations.end(), [&anim] (const Animation* a) { return a->getName() == anim->getName(); }) == animations.end())
    {
        animations.push_back(anim);
    }
}

void prim::AnimationPlayer::play()
{
    if(!playing && currentAnimation)
    {
        playing = true;
    }
}

void prim::AnimationPlayer::play(std::string_view animationName)
{
    if(currentAnimation && currentAnimation->getName() == animationName) return;
    auto anim = std::find_if(animations.begin(), animations.end(), [&animationName] (const Animation* a) { return a->getName() == animationName; });
    if(anim != animations.end())
    {
        currentAnimation = *anim;
        playing = true;
    }
    else
    {
        std::cerr << "Couldn't find animation with name: " << animationName << std::endl;
    }
}

void prim::AnimationPlayer::stop()
{
    playing = false;
    playtime = 0.0f;
}

void prim::AnimationPlayer::pause()
{
    playing = false;
}

void prim::AnimationPlayer::update(float deltaTime)
{
    UPDATE_OVERRIDE 

    if(playing)
    {
        playtime += deltaTime;
        if(playtime > currentAnimation->getLength()) 
        {
            playtime = 0.0f;
            if(!currentAnimation->loop) stop();
        }
        currentAnimation->update(playtime);
    }
}

//////////////////////