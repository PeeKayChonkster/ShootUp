#ifndef PRIM_TRANSFORM2D
#define PRIM_TRANSFORM2D

#include <vector>
#include <raylib-cpp.hpp>


namespace prim
{
    class Transform2D
    {
    private:
        raylib::Transform2D transform;
    public:
        class Node2D* node;
        Transform2D* parent;
        std::vector<Transform2D*> children;

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
        void lookAt(raylib::Vector2 point);

        raylib::Transform2D getRaylibTransform() const;

        // this function is dangerous, child transform pointer could be non-constant (if it's inside of std::vector for example)
        void addChild(Node2D* child);
        void removeChild(Node2D* child);
    };
}

#endif // prim_TRANSFORM2D