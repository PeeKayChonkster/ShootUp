#include "node.hpp"
#include "debug.hpp"
#include "prim_exception.hpp"
#include <algorithm>

//// static members /////
bool prim::Node::nodeCache[MAX_NODES] = { false };
/////////////////////////

prim::Node::Node(std::string name) : name(name)
{
    int newId = getNewId();
    if(newId < 0) throw PRIM_EXCEPTION("Engine gave out all IDs or this node already has an ID.");
    else id = static_cast<uint16_t>(newId);
}

prim::Node::~Node()
{
    nodeCache[id] = false;
}

int prim::Node::getNewId()
{
    if(id) return -1; // return if node already has an id
    for(int i = 0; i < MAX_NODES; ++i)
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

void prim::Node::startChildren()
{
    for(uint i = 0u; i < children.size(); ++i)
    {
        children[i]->start();
    }
}

void prim::Node::updateChildren(float deltaTime)
{
    for(uint i = 0u; i < children.size(); ++i)
    {
        children[i]->update(deltaTime);
    }
}

void prim::Node::drawChildren()
{
    for(uint i = 0u; i < children.size(); ++i)
    {
        children[i]->draw();
    }
}

uint16_t prim::Node::getId() const
{
    return id;
}

void prim::Node::start()
{
    // First, call children's start methods, then execute own start method
    START_OVERRIDE

    ///// start() code for this node starts from here /////
    ///////////////////////////////////////////////////////
}

void prim::Node::update(float deltaTime)
{
    // First, call children's update methods, then execute own update method
    UPDATE_OVERRIDE

    ///// update() code for this node starts from here /////
    ////////////////////////////////////////////////////////
}

void prim::Node::draw()
{
    // First, call children's draw methods, then execute own draw method
    DRAW_OVERRIDE

    ///// draw() code for this node starts from here /////
    //////////////////////////////////////////////////////
}

void prim::Node::addChild(Node* child)
{
    auto predicate = [&](Node* ch) { return (ch->getId() == child->getId() && ch->name == child->name); };
    if(std::find_if(children.begin(), children.end(), predicate) == children.end())
    {
        children.push_back(child);
        child->parent = this;
    }
    else
    {
        throw PRIM_EXCEPTION("Trying to add child with the same name/id. Parent: " + name + "; Child: " + child->name);
    }
}

void prim::Node::removeChild(Node* child)
{
    auto predicate = [&](Node* ch) { return ch->getId() == child->getId(); };
    auto childIter = std::find_if(children.begin(), children.end(), predicate);
    if(childIter != children.end())
    {
        children.erase(childIter);
        child->parent = nullptr;
    }
}