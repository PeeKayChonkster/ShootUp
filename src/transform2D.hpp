#ifndef PRIM_TRANSFORM2D
#define PRIM_TRANSFORM2D

#include <raylib-cpp.hpp>


namespace prim
{
    class Transform2D
    {
    private:
        raylib::Transform2D transform;

    public:
        class Node2D* owner;

        Transform2D(Node2D* owner);
        Transform2D(const Transform2D& other) = delete;

        raylib::Vector2 getGlobalPosition() const;
        float getGlobalRotation() const;
        raylib::Vector2 getGlobalScale() const;

        raylib::Vector2 getLocalPosition() const;
        float getLocalRotation() const;
        raylib::Vector2 getLocalScale() const;

        void setLocalPosition(raylib::Vector2 position);
        void setLocalRotation(float rotation);
        void setLocalScale(raylib::Vector2 scale);

        void setGlobalPosition(raylib::Vector2 position);
        void setGlobalRotation(float rotation);
        void setGlobalScale(raylib::Vector2 scale);

        void move(raylib::Vector2 translation);
        void rotate(float angle);
        void scaleUp(raylib::Vector2 scaleOffset);
        void lookAt(raylib::Vector2 point);

        raylib::Transform2D getRaylibTransform() const;
    };
}

#endif // prim_TRANSFORM2D