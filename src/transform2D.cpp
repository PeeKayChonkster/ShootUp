#include "transform2D.hpp"
#include <raymath.h>
#include <algorithm>
#include "node2D.hpp"

prim::Transform2D::Transform2D(Node2D* owner) : owner(owner) {}

raylib::Vector2 prim::Transform2D::getGlobalPosition() const
{
    Node2D* parent = dynamic_cast<Node2D*>(owner->parent);
    if(parent)
    {
        return parent->transform.getGlobalPosition() + getLocalPosition();
    }
    else
    {
        return getLocalPosition();
    }
}
    

float prim::Transform2D::getGlobalRotation() const
{
    Node2D* parent = dynamic_cast<Node2D*>(owner->parent);
    if(parent)
    {
        return parent->transform.getGlobalRotation() + getLocalRotation(); 
    }
    else
    {
        return getLocalRotation();
    }
}

raylib::Vector2 prim::Transform2D::getGlobalScale() const
{
    Node2D* parent = dynamic_cast<Node2D*>(owner->parent);
    raylib::Vector2 localScale = getLocalScale();
    raylib::Vector2 globalScale = raylib::Vector2::One();
    if(parent)
    {
        globalScale = parent->transform.getGlobalScale();
    }
    return raylib::Vector2{ localScale.x * globalScale.x, localScale.y * globalScale.y };
}

raylib::Vector2 prim::Transform2D::getLocalPosition() const
{
    return transform.translation;
}

float prim::Transform2D::getLocalRotation() const
{
    return transform.rotation;
}

raylib::Vector2 prim::Transform2D::getLocalScale() const
{
    return transform.scale;
}

void prim::Transform2D::setLocalPosition(raylib::Vector2 position)
{
    transform.translation = position;
}

void prim::Transform2D::setLocalRotation(float rotation)
{
    transform.rotation = rotation;
}

void prim::Transform2D::setLocalScale(raylib::Vector2 scale)
{
    transform.scale = scale;
}

void prim::Transform2D::setGlobalPosition(raylib::Vector2 position)
{
    transform.translation = position - getGlobalPosition();
}

void prim::Transform2D::setGlobalRotation(float rotation)
{
    transform.rotation = rotation - getGlobalRotation();
}

void prim::Transform2D::setGlobalScale(raylib::Vector2 scale)
{
    raylib::Vector2 globalScale = getGlobalScale();
    transform.scale.x = scale.x / globalScale.x;
    transform.scale.y = scale.y / globalScale.y;
}


void prim::Transform2D::move(raylib::Vector2 translate)
{
    transform.translation += translate; 
}

void prim::Transform2D::rotate(float angle)
{
    transform.rotation += angle;
}

void prim::Transform2D::scaleUp(raylib::Vector2 scaleOffset)
{
    transform.scale += scaleOffset;
}

void prim::Transform2D::lookAt(raylib::Vector2 point)
{
    //  WASN'T TESTED!
    transform.rotation = point.Angle(raylib::Vector2::Right());
}

raylib::Transform2D prim::Transform2D::getRaylibTransform() const
{
    return transform;
}
