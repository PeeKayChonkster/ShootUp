#include "node_library.hpp"
#include <algorithm>
#include <iostream>

/// InputController ///

prim::InputController::InputController(std::string name, Node2D* target): Node(name), target(target) {}
prim::InputController::~InputController() {}

void prim::InputController::update(float deltaTime)
{
    UPDATE_OVERRIDE
    if(IsKeyDown(KEY_D) || IsKeyDown(KEY_S) || IsKeyDown(KEY_W))
    {
        targetAnimPlayer->play("walk");
    }
    else if(IsKeyDown(KEY_A))
    {
        targetAnimPlayer->play("walk");
    }
    else
        targetAnimPlayer->play("idle");
    
    if(IsKeyDown(KEY_D)) target->transform.move({ 1.0f, 0.0f});
    if(IsKeyDown(KEY_S)) target->transform.move({ 0.0f, 1.0f});
    if(IsKeyDown(KEY_A)) target->transform.move({ -1.0f, 0.0f});
    if(IsKeyDown(KEY_W)) target->transform.move({ 0.0f, -1.0f});
    if(IsKeyDown(KEY_Q)) target->transform.rotate(1.0f);
    if(IsKeyDown(KEY_E)) target->transform.rotate(-1.0f);
    if(IsKeyDown(KEY_U)) target->transform.scaleUp({ 0.0f, 0.1f });
    if(IsKeyDown(KEY_J)) target->transform.scaleUp({ 0.0f, -0.1f });
    if(IsKeyDown(KEY_I)) target->transform.scaleUp({ 0.1f, 0.0f });
    if(IsKeyDown(KEY_Y)) target->transform.scaleUp({ -0.1f, 0.0f });

}

void prim::InputController::start()
{
    START_OVERRIDE;

    targetAnimPlayer = target->getChild<AnimationPlayer>("animationPlayer");
    if(!targetAnimPlayer) throw PRIM_EXCEPTION("InputController couldn't find target's animation player. Target: " + target->name);
}

///////////////////////


/// AnimationPlayer ///

prim::AnimationPlayer::AnimationPlayer(std::string name): Node(name) {}

prim::AnimationPlayer::~AnimationPlayer()
{
    for(int i = 0; i < animations.size(); ++i)
    {
        delete animations[i];
    }
}

/*
    * Create and push new Animation.
*/
prim::Animation* prim::AnimationPlayer::createAnimation(std::string name, float length, uint16_t frameCount)
{
    Animation* anim = new Animation(name, length, frameCount);
    pushAnimation(anim);
    return anim;
}


/*
    * Create and push new SpriteAnimation.
*/
prim::SpriteAnimation* prim::AnimationPlayer::createAnimation(std::string name, float length, Sprite* target)
{
    SpriteAnimation* anim = new SpriteAnimation(name, length, target);
    pushAnimation(anim);
    return anim;
}

void prim::AnimationPlayer::pushAnimation(AnimationBase* anim)
{
    // If animation isn't already exists in the vector
    if(std::find_if(animations.begin(), animations.end(), [&anim] (const AnimationBase* a) { return a->getName() == anim->getName(); }) == animations.end())
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
    stop();
    auto anim = std::find_if(animations.begin(), animations.end(), [&animationName] (const AnimationBase* a) { return a->getName() == animationName; });
    if(anim != animations.end())
    {
        currentAnimation = *anim;
        playing = true;
    }
    else
    {
        throw PRIM_EXCEPTION("Couldn't find animation with name: " + std::string(animationName));
    }
}

void prim::AnimationPlayer::stop()
{
    playing = false;
    playtime = 0.0f;
    if(currentAnimation) currentAnimation->reset();
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