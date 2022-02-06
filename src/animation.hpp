#ifndef PRIM_ANIMATION
#define PRIM_ANIMATION
#include <vector>
#include <utility>
#include <cmath>
#include <cinttypes>

namespace prim
{


//------ HELPER CLASSES ------//
template<class T>
struct AnimationPoint
{
    float timePoint;
    T value;
};


class AnimationStripBase
{
private:
public:
    bool interpolate = false;
    virtual void updateCurrentPoint(float playtime) = 0;
};


template<class T>
class AnimationStrip : public AnimationStripBase
{
private:
    AnimationStrip() = delete;
    AnimationStrip(const AnimationStrip& other) = delete;
    AnimationStrip(std::vector<AnimationPoint<T>>&& points) : animationPoints(std::move(points)), currentPoint(animationPoints[0]) {}

    friend class Animation;
    friend class AnimationOneStrip;

    /*
    * Given the playtime, find closest animationPoint to that time and return it's index
    */
    inline AnimationPoint<T> findClosestPoint(float playtime) const
    {
        // index and time difference pair
        std::pair<uint16_t, float> point { 0u, std::abs(animationPoints[0].timePoint - playtime)};
        for(int i = 0; i < animationPoints.size(); ++i)
        {
            float diffence = std::abs(animationPoints[i].timePoint - playtime);
            if(diffence < point.second()) point = { i, difference };
        }
        return animationPoints[point.first];
    }

    /*
    * Given the playtime, find two closest animation points and interpolate between them
    */
    inline AnimationPoint<T> interpolatePoint(float playtime)
    {
        if(playtime == 0.0f) return animationPoints[0];
        if(playtime >= animationPoints.back().timePoint) return animationPoints.back();
        uint16_t firstIdx, secondIdx = 0u;
        for(uint16_t i = 0; i < animationPoints.size(); ++i)
        {
            if(playtime >= animationPoints[i].timePoint && playtime <= animationPoints[i+1].timePoint)
            {
                firstIdx = i;
                secondIdx = i + 1;
                break;
            }
        }
        float timeBetweenPoints = animationPoints[secondIdx].timePoint - animationPoints[firstIdx].timePoint;
        float playtimeOffset = playtime - animationPoints[firstIdx].timePoint;
        return AnimationPoint<T> { playtime, std::lerp(animationPoints[firstIdx].value, animationPoints[secondIdx].value, playtimeOffset / timeBetweenPoints)};
    }

public:
    std::vector<AnimationPoint<T>> animationPoints;
    AnimationPoint<T> currentPoint;

    inline virtual void updateCurrentPoint(float playtime) override
    {
        if(interpolate)
        {
            currentPoint = interpolatePoint(playtime);
        }
        else
        {
            currentPoint = findClosestPoint(playtime);
        }
    }

    inline AnimationPoint<T> getCurrentPoint() const
    {
        return currentPoint;
    }
};
//---------------------------------------------------//



class Animation
{
private:
    std::string name;
    std::vector<AnimationStripBase*> animationStrips;
    float playtime = 0.0f;
    float length = 0.0f;
    uint16_t frameCount = 0u;
    float timestep = 0.0f;
public:
    Animation() = delete;
    Animation(std::string name, float length, uint16_t frameCount) : name(name), length(length), frameCount(frameCount), timestep(length / frameCount) {}
    ~Animation()
    {
        for(int i = 0; i < animationStrips.size(); ++i)
        {
            delete animationStrips[i];
        }
    }

    template<class T>
    inline void createStrip(std::vector<AnimationPoint<T>>&& points)
    {
        animationStrips.push_back(new AnimationStrip(std::move(points)));
    }

    inline void removeStrip(AnimationStripBase* strip)
    {
        for(auto iter = animationStrips.begin(); iter != animationStrips.end(); ++iter)
        {
            if(*iter == strip)
            {
                delete *iter;
                animationStrips.erase(iter);
                break;
            }
        }
    }
};


template<class T>
class AnimationOneStrip : public Animation
{
private:
    std::string name;
    AnimationStripBase* strip;
    float playtime = 0.0f;
    float length = 0.0f;
    uint16_t frameCount = 0u;
    float timestep = 0.0f;
public:
    AnimationOneStrip() = delete;
    AnimationOneStrip(const AnimationOneStrip& other) = delete;
    AnimationOneStrip(std::string name, std::vector<AnimationPoint<T>>&& points) : 
        name(name), strip(new AnimationStrip<T>(points)), 
        length(strip.animationPoints.back().timePoint),
        frameCount(strip.animationPoints.size()),
        timestep(length / frameCount)
        {}
    ~AnimationOneStrip() { delete strip; }
};


class AnimationPlayer
{

};

} // namespace prim

#endif // PRIM_ANIMATION