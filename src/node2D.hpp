#ifndef PRIM_NODE2D
#define PRIM_NODE2D

#include <string>
#include "transform2D.hpp"

namespace prim
{
    #define MAX_NODES 1000
    #define NODE2D_INHERIT friend class App;
    #define START_OVERRIDE startChildren();
    #define UPDATE_OVERRIDE updateChildren(deltaTime);
    #define DRAW_OVERRIDE if(!visible) return; drawChildren();      // ?: Maybe override macros should call parent method instead of calling children methods?

    class Drawable
    {
    public:
        bool visible = true;
        bool drawWires = false;
        virtual void draw() = 0;
    };


    class Runnable
    {
    public:
        virtual void start() = 0;
        virtual void update(float deltaTime) = 0;
    };


    class Node2D
    {
    private:
        uint16_t id = 0;
        static bool nodeCache[MAX_NODES];
        
        int getNewId();

    protected:
        void startChildren();
        void updateChildren(float deltaTime);
        void drawChildren();

        Node2D() = delete;
        Node2D(const Node2D& other) = delete;
        Node2D(std::string name);

        friend class App;

    public:
        virtual ~Node2D();

        prim::Transform2D transform;
        std::string name;
        bool visible = true;

        uint16_t getId() const;

        virtual void start();
        virtual void update(float deltaTime);
        virtual void draw();
    };
}
#endif // PRIM_NODE2D