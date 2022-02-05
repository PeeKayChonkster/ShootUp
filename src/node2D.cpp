#include "node2D.hpp"
#include "prim_exception.hpp"
#include <algorithm>
#include "debug.hpp"

//// static members /////
bool prim::Node2D::nodeCache[MAX_NODES] = { false };

/*
    * 
*/
int prim::Node2D::getNewId()
{
    if(id) return -1; // return if node already has an id
    for(uint16_t i = 0u; i < MAX_NODES; ++i)
    {
        if(!nodeCache[i]) 
        {
            prim::Debug::printPersistentLine("Gave out id=" + std::to_string(i) + " to node \"" + this->name + "\"");
            nodeCache[i] = true;
            return i;
        }
    }
    return -1;
}
/////////////////////////


prim::Node2D::Node2D() : Node2D("_noname_") {}

prim::Node2D::Node2D(std::string name) : name(name), transform()
{
    if(int newId = getNewId() < 0) throw PRIM_EXCEPTION("Engine gave out all IDs or this node already has an ID.");
    else id = static_cast<uint16_t>(newId);
    transform.node = this;
}

prim::Node2D::~Node2D()
{
    nodeCache[id] = false;
}

// void prim::Node::draw()
// {
//     if(visible)
//     {
//         // apply rotation to model
//         model.index()
//         model.SetTransform(transform.getGlobalRotation().ToMatrix());
//         // apply translation to model
//         model.Draw(transform.getGlobalPosition());
//         if(drawWires) model.DrawWires(transform.getGlobalPosition(), 1.0f, BLACK);
//         for(Node* ch : transform.children)
//         {
//             ch->draw();
//         }
//     }
// }

void prim::Node2D::startChildren()
{
    for(uint i = 0u; i < transform.children.size(); ++i)
    {
        transform.children[i]->node->start();
    }
}

void prim::Node2D::updateChildren(float deltaTime)
{
    for(uint i = 0u; i < transform.children.size(); ++i)
    {
        transform.children[i]->node->update(deltaTime);
    }
}

void prim::Node2D::drawChildren()
{
    for(uint i = 0u; i < transform.children.size(); ++i)
    {
        transform.children[i]->node->draw();
    }
}

uint16_t prim::Node2D::getId() const
{
    return id;
}

void prim::Node2D::start()
{
    // First, call children's start methods, then execute own start method
    START_OVERRIDE

    ///// start() code for this node starts from here /////
    ///////////////////////////////////////////////////////
}

void prim::Node2D::update(float deltaTime)
{
    // First, call children's update methods, then execute own update method
    UPDATE_OVERRIDE

    ///// update() code for this node starts from here /////
    ////////////////////////////////////////////////////////
}

void prim::Node2D::draw()
{
    // First, call children's draw methods, then execute own draw method
    DRAW_OVERRIDE

    ///// draw() code for this node starts from here /////
    //////////////////////////////////////////////////////
}
