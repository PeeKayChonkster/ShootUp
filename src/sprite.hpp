#ifndef PRIM_SPRITE
#define PRIM_SPRITE

#include "node2D.hpp"

namespace prim
{

class Sprite : public Node2D
{
private:
    raylib::Texture2D texture;

public:
    Sprite() = delete;
    Sprite(const Sprite&& other) = delete;
    Sprite(std::string texturePath, std::string nodeName);

    raylib::Color tint = { 255, 255, 255 };

    virtual void draw() override;
};

}

#endif // PRIM_SPRITE