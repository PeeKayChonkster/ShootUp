#include "node_library.hpp"
#include <algorithm>

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

prim::AnimationPlayer::~AnimationPlayer()
{
    for(int i = 0; i < animations.size(); ++i)
    {
        delete animations[i];
    }
}

void prim::AnimationPlayer::pushAnimation(Animation* anim)
{
    // If animation isn't already exists in the vector
    if(std::find_if(animations.begin(), animations.end(), [&anim] (const Animation* a) { a->getName() == anim->getName(); }) == animations.end())
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
    auto anim = std::find_if(animations.begin(), animations.end(), [&animationName] (const Animation* a) { a->getName() == animationName; });
    if(anim != animations.end())
    {
        currentAnimation = *anim;
        playing = true;
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
        
    }
}

//////////////////////