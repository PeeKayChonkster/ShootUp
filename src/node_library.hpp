#ifndef PRIM_NODE_LIBRARY
#define PRIM_NODE_LIBRARY

#include "node2D.hpp"

namespace prim
{

class InputController : public Node2D
{
private:
    NODE2D_INHERIT
    
    Node2D* target;
protected:
    InputController() = delete;
    InputController(std::string name, Node2D* target);
public:
    virtual void update(float deltaTime) override;
};

}

#endif // PRIM_NODE_LIBRARY