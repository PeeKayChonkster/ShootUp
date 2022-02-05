#include "sprite.hpp"

prim::Sprite::Sprite(std::string texturePath, std::string nodeName): Node2D(nodeName), texture(texturePath) {}

void prim::Sprite::draw()
{
    DRAW_OVERRIDE

    raylib::Vector2 globalScale = transform.getGlobalScale();
    raylib::Rectangle destRec(transform.getGlobalPosition(), texture.GetSize());
    destRec.width *= globalScale.x;
    destRec.height *= globalScale.y;
    raylib::Vector2 origin(texture.GetSize());
    origin.x *= globalScale.x * 0.5f;
    origin.y *= globalScale.y * 0.5f;
    texture.Draw(raylib::Rectangle(raylib::Vector2::Zero(), texture.GetSize()), destRec, origin, transform.getGlobalRotation(), tint);
}