#ifndef PRIM_NODE_LIBRARY
#define PRIM_NODE_LIBRARY

#include "node2D.hpp"
#include "animation.hpp"

namespace prim
{

class InputController : public Node2D
{
private:
    NODE2D_INHERIT
    
    Node2D* target;
protected:
    InputController() = delete;
    InputController(std::string name, Node2D* target);
public:
    virtual void update(float deltaTime) override;
};


class AnimationPlayer : public Node2D
{
private:
    float playtime = 0.0f;
    std::vector<Animation*> animations;
    Animation* currentAnimation;
    bool playing = false;
public:
    ~AnimationPlayer();
    void pushAnimation(Animation* anim);
    void play();
    void play(std::string_view animationName);
    void stop();
    void pause();
    inline Animation* getCurrentAnimation() const { return currentAnimation; }
    inline bool isPlaying() const { return playing; }

    void update(float deltaTime) override;
};

}

#endif // PRIM_NODE_LIBRARY