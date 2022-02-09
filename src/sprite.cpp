#include "sprite.hpp"
#include <algorithm>
#include "debug.hpp"

prim::Sprite::Sprite(std::string nodeName, std::string texturePath): Sprite(nodeName, texturePath, 1u, 1u) {}

prim::Sprite::Sprite(std::string nodeName, std::string texturePath, uint16_t hframeCount, uint16_t vframeCount): 
    Node2D(nodeName), 
    texture(texturePath), 
    hframeCount(hframeCount),
    vframeCount(vframeCount)
{
    srcRect = { raylib::Vector2::Zero(), raylib::Vector2(texture.GetWidth() / hframeCount, texture.GetHeight() / vframeCount) };
}

void prim::Sprite::draw()
{
    DRAW_OVERRIDE

    srcRect.x = hframe % hframeCount * srcRect.GetWidth();
    srcRect.y = vframe % vframeCount * srcRect.GetHeight();
    // origin is always at center of srcRect
    raylib::Rectangle destRec(transform.getGlobalPosition(), srcRect.GetSize());
    raylib::Vector2 globalScale = transform.getGlobalScale();
    destRec.width *= globalScale.x;
    destRec.height *= globalScale.y;
    // To remember: origin is local to the sourceRec!!!
    raylib::Vector2 origin(srcRect.GetWidth() * 0.5f, srcRect.GetHeight() * 0.5f);
    origin.x *= globalScale.x;
    origin.y *= globalScale.y;
    texture.Draw(srcRect, destRec, origin, transform.getGlobalRotation(), tint);
    // DEBUG //
    Debug::printLine("hframe: " + std::to_string(hframe));
    DrawPixel(transform.getGlobalPosition().x, transform.getGlobalPosition().y, RED);
    ///////////
}