#ifndef PRIM_NODE_LIBRARY
#define PRIM_NODE_LIBRARY

#include "node2D.hpp"
#include "animation.hpp"

namespace prim
{

class InputController : public Node
{
private:
    Node2D* target;
    class AnimationPlayer* targetAnimPlayer = nullptr;
protected:
public:
    InputController(std::string name, Node2D* target);
    virtual ~InputController();
    virtual void update(float deltaTime) override;
    virtual void start() override;
};


class AnimationPlayer : public Node
{
private:
    float playtime = 0.0f;
    std::vector<AnimationBase*> animations;
    AnimationBase* currentAnimation = nullptr;
    bool playing = false;
public:
    AnimationPlayer(std::string name = "_noname_");
    virtual ~AnimationPlayer();
    Animation* createAnimation(std::string name, float length, uint16_t frameCount);
    SpriteAnimation* createAnimation(std::string name, float length, Sprite* target);
    void pushAnimation(AnimationBase* anim);
    void play();
    void play(std::string_view animationName);
    void stop();
    void pause();
    inline AnimationBase* getCurrentAnimation() const { return currentAnimation; }
    inline bool isPlaying() const { return playing; }

    void update(float deltaTime) override;
};

}

#endif // PRIM_NODE_LIBRARY