#ifndef PRIM_ANIMATION
#define PRIM_ANIMATION
#include <vector>
#include <utility>
#include <cmath>
#include <cinttypes>
#include <string_view>

namespace prim
{

//------ HELPER FUNCTION ------//
template<class T>
T lerp(const T& a, const T& b, float t)
{
    return a + t(b - a);
}


template<class T>
struct AnimationPoint
{
    float timePoint;
    T value;
};





class Animation
{
private:

        //------ HELPER CLASSES ------//
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
        std::vector<AnimationPoint<T>> animationPoints;
        AnimationPoint<T> currentPoint;
        T* valueToAnimate

        /*
        * Given the playtime, floor it to the left nearest animation point at return that point
        */
        inline AnimationPoint<T> floorCurrentPoint(float playtime) const
        {
            static_assert(!animationPoints.empty(), "Trying to update empty animation strip.");
            if(playTime <= animationPoints[0].timePoint) return animationPoints[0];
            if(playTime >= animationPoints.back().timePoint) return animationPoints.back();
            for(int i = 0; i < animationPoints.size(); ++i)
            {
                if(animationPoints[i].timePoint <= playTime && animationPoints[i+1] > playTime)
                {
                    currentPoint = animationPoints[i];
                    return currentPoint;
                }
            }
        }

        /*
        * Given the playtime, find two closest animation points and interpolate between them
        */
        inline AnimationPoint<T> interpolateCurrentPoint(float playtime)
        {
            static_assert(!animationPoints.empty(), "Trying to update empty animation strip.");
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
            return AnimationPoint<T> { playtime, lerp(animationPoints[firstIdx].value, animationPoints[secondIdx].value, playtimeOffset / timeBetweenPoints)};
        }

    public:
        AnimationStrip() = delete;
        AnimationStrip(const AnimationStrip& other) = delete;
        AnimationStrip(T* valueToAnimate, std::vector<AnimationPoint<T>>&& points) : 
                animationPoints(std::move(points)), 
                currentPoint(animationPoints[0]), 
                valueToAnimate(valueToAnimate) 
                {}

        inline virtual void updateCurrentPoint(float playtime) override
        {
            if(interpolate)
            {
                currentPoint = interpolateCurrentPoint(playtime);
            }
            else
            {
                currentPoint = floorCurrentPoint(playtime);
            }
            *valueToAnimate = currentPoint.value;
        }

        inline AnimationPoint<T> getCurrentPoint() const
        {
            return currentPoint;
        }
    };
    //---------------------------------------------------//

protected:
    std::string name;
    std::vector<AnimationStripBase*> animationStrips;
    float playtime = 0.0f;
    float length;
    uint16_t frameCount;
    float timestep;

    Animation() = delete;
    Animation(const Animation& other) = delete;
    Animation(std::string name, float length, uint16_t frameCount) : name(name), length(length), frameCount(frameCount), timestep(length / frameCount) {}
public:
    ~Animation()
    {
        for(int i = 0; i < animationStrips.size(); ++i)
        {
            delete animationStrips[i];
        }
    }

    inline static Animation* createAnimation(std::string name, float length, uint16_t frameCount)
    {
        return new Animation(name, length, frameCount);
    }

    template<class T>
    inline void createStrip(T* valueToAnimate, std::vector<AnimationPoint<T>>&& points)
    {
        animationStrips.push_back(new AnimationStrip<T>(valueToAnimate, std::move(points)));
    }

    inline void update()
    {
        for(auto& strip : animationStrips)
        {
            strip->updateCurrentPoint(playtime);
        }
    }

    inline std::string_view getName() const
    {
        return name;
    }
};

} // namespace prim

#endif // PRIM_ANIMATION