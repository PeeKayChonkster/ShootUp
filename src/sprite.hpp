#ifndef PRIM_SPRITE
#define PRIM_SPRITE

#include "node2D.hpp"

namespace prim
{

class Sprite : public Node2D
{
private:
    raylib::Texture2D texture;
    raylib::Rectangle srcRect;
    uint16_t hframeCount;
    uint16_t vframeCount;

public:
    Sprite() = delete;
    Sprite(const Sprite&& other) = delete;
    Sprite(std::string nodeName, std::string texturePath);
    Sprite(std::string nodeName, std::string texturePath, uint16_t hframeCount, uint16_t vframeCount);

    uint16_t vframe = 0u;
    uint16_t hframe = 0u;
    raylib::Color tint = { 255, 255, 255 };

    virtual void draw() override;
};

}

#endif // PRIM_SPRITE