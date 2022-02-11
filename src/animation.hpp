#ifndef PRIM_ANIMATION
#define PRIM_ANIMATION
#include <vector>
#include <utility>
#include <cmath>
#include <cinttypes>
#include <string_view>
#include <optional>
#include <algorithm>
#include "debug.hpp"
#include "prim_exception.hpp"
#include "resman.hpp"
#include "sprite.hpp"

namespace prim
{

//------ HELPER FUNCTION ------//
template<class T>
T lerp(const T& a, const T& b, float t)
{
    return a + t*(b - a);
}


template<class T>
struct AnimationPoint
{
    uint16_t frame;
    T value;
};


class AnimationBase
{
protected:
    std::string name;
    float length;
    uint16_t frameCount;

public:
    AnimationBase(std::string name, float length, uint16_t frameCount) : name(name), length(length), frameCount(frameCount) {}
    virtual ~AnimationBase() {}

    bool loop = true;
    bool mirrored = false;
    inline std::string_view getName() const { return name; }
    inline float getLength() const { return length; }
    virtual void update(float playtime) = 0;
    virtual void reset() = 0;
};


class Animation : public AnimationBase
{
private:

    //---------------- HELPER CLASSES ------------------//
    class AnimationStripBase
    {
    private:
    public:
        bool interpolate = false;
        virtual void setFrame(uint16_t frame) = 0;
    };


    template<class T>
    class AnimationStrip : public AnimationStripBase
    {
    private:
        std::vector<std::optional<T>> animationValues;
        T* valueToAnimate;
        uint16_t currentFrame = 0u;

    public:
        AnimationStrip() = delete;
        AnimationStrip(const AnimationStrip& other) = delete;
        AnimationStrip(T* valueToAnimate, uint16_t gridCount, std::vector<AnimationPoint<T>>&& points) : 
                valueToAnimate(valueToAnimate),
                animationValues(gridCount, std::nullopt)
        {
            for(auto& p : points)
            {
                if(p.frame > gridCount - 1u) throw PRIM_EXCEPTION("Adding animation point with frameNumber higher than animation frameCount.");
                animationValues[p.frame] = p.value;
            }
        }

        inline void setFrame(uint16_t frame) override
        {
            if(frame == currentFrame) return;
            if(animationValues[frame])
            {
                *valueToAnimate = animationValues[frame].value();
                currentFrame = frame;
            }
            else if(interpolate)
            {
                // TODO: Implement point interpolation.

                uint16_t nextFrame = 0u;
                uint16_t nextFrameOffset = 0u;
                for(uint16_t i = currentFrame + 1u; i < animationValues.size(); ++i)
                {
                    ++nextFrameOffset;
                    if(animationValues[i])
                    {
                        nextFrame = i;
                        break;
                    }
                }
                if(nextFrame)
                {
                    float ratio = (nextFrame - frame) / nextFrameOffset;
                    *valueToAnimate = lerp(animationValues[currentFrame].value(), animationValues[nextFrame].value(), (nextFrame - frame) / nextFrame);
                }
            }
        }
    };
    //---------------------------------------------------// HELPER CLASSES

protected:
    std::vector<AnimationStripBase*> animationStrips;
    float timestep;
public:
    Animation(const Animation& other) = delete;
    Animation(std::string name, float length, uint16_t frameCount) : AnimationBase(name, length, frameCount), timestep(length/frameCount) {}
    virtual ~Animation() override
    {
        for(int i = 0; i < animationStrips.size(); ++i)
        {
            delete animationStrips[i];
        }
    }
    
    /*
        * Create custom animation strip with arbitrary value to animate. Animation frames in the grid can be skipped, f.e.: {{0u, 12.3f},{5u, 1.8f}}.
    */

    template<class T>
    inline void createStrip(T* valueToAnimate, std::vector<AnimationPoint<T>>&& points)
    {
        animationStrips.push_back(new AnimationStrip<T>(valueToAnimate, frameCount, std::move(points)));
    }


    /*
        * Create simple uint16_t strip with equal offset between animation points.
    */
    inline void createStrip(uint16_t* valueToAnimate, uint16_t firstValue, uint16_t increment = 1u)
    {
        std::vector<AnimationPoint<uint16_t>> points;
        points.push_back({ 0u, firstValue });
        for(uint16_t i = 1u; i < frameCount; ++i)
        {
            AnimationPoint<uint16_t> point = {i, uint16_t(i * increment)};
            points.emplace_back(std::move(point));
        }
        animationStrips.push_back(new AnimationStrip<uint16_t>(valueToAnimate, frameCount, std::move(points)));
    }

    inline void update(float playtime) override
    {
        uint16_t frame = std::clamp<uint16_t>(std::floor(playtime / timestep), 0u, frameCount);
        /// DEBUG ///
        Debug::printLine("Animation: " + name);
        Debug::printLine("animFrame: " + std::to_string(frame));
        Debug::printLine("playtime: " + std::to_string(playtime));
        /////////////
        std::for_each(animationStrips.begin(), animationStrips.end(), [&frame](AnimationStripBase* strip){ strip->setFrame(frame); });
    }

    inline void reset() override {}

    inline uint16_t getFrameCount() const { return frameCount; }
};


class SpriteAnimation : public AnimationBase
{
private:
    std::vector<raylib::Texture2D*> textures;
    float timestep;
    Sprite* target;
    uint16_t currentFrame = 0u;
    raylib::Texture2D* initialTexture = nullptr;

public:
    SpriteAnimation(std::string name, float length, Sprite* target) : AnimationBase(name, length, 0u), timestep(length), target(target), initialTexture(target->texture) {}
    virtual ~SpriteAnimation() override
    {
        std::for_each(textures.begin(), textures.end(), [](raylib::Texture2D* texture){ delete texture; });
    }


    /*
        * Load image file from disk and push into animation.
    */
    inline void pushImage(std::string imagePath)
    {
        textures.push_back(Resman::loadTexture(imagePath));
        ++frameCount;
        timestep = length / frameCount;
    }

    inline void update(float playtime) override
    {
        uint16_t frame = std::clamp<uint16_t>(std::floor(playtime / timestep), 0u, frameCount);
        /// DEBUG ///
        Debug::printLine("Animation: " + name);
        Debug::printLine("animFrame: " + std::to_string(frame));
        Debug::printLine("playtime: " + std::to_string(playtime));
        /////////////
        if(frame != currentFrame)
        {
            target->swapTexture(textures[frame]);
            currentFrame = frame;
        }
    }

    inline void reset() override
    {
        target->swapTexture(initialTexture);
    }
};

} // namespace prim

#endif // PRIM_ANIMATION