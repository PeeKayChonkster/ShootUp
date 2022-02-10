#ifndef PRIM_NODE2D_HPP
#define PRIM_NODE2D_HPP

#include "transform2D.hpp"
#include "node.hpp"

namespace prim
{
    class Node2D : public Node
    {
    public:
        Node2D() = delete;
        Node2D(const Node2D& other) = delete;
        Node2D(std::string name);
        virtual ~Node2D();

        prim::Transform2D transform;
    };
}
#endif // PRIM_NODE2D_HPP