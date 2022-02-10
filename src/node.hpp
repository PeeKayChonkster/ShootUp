#ifndef PRIM_NODE_HPP
#define PRIM_NODE_HPP

#include <cinttypes>
#include <string>
#include <vector>

namespace prim
{

#define MAX_NODES 1000
#define START_OVERRIDE startChildren();
#define UPDATE_OVERRIDE updateChildren(deltaTime);
#define DRAW_OVERRIDE if(!visible) return; drawChildren();      // ?: Maybe override macros should call parent method instead of calling children methods?

class Node
{
private:
    uint16_t id = 0u;
    static bool nodeCache[MAX_NODES];

    int getNewId();
    
protected:
    void startChildren();
    void updateChildren(float deltaTime);
    void drawChildren();

public:
    Node() = delete;
    Node(const Node& other) = delete;
    Node(std::string name);
    virtual ~Node();

    std::string name;
    bool visible = true;
    std::vector<Node*> children;
    Node* parent = nullptr;

    uint16_t getId() const;

    virtual void start();
    virtual void update(float deltaTime);
    virtual void draw();

    void addChild(Node* child);
    void removeChild(Node* child);
};

} // namespace prim


#endif // PRIM_NODE_HPP