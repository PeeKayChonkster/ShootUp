#ifndef PRIM_APP
#define PRIM_APP

#include "node2D.hpp"
#include "node_library.hpp"
#include <raylib-cpp.hpp>
#include <type_traits>


namespace prim
{
    
class App
{
private:
    Node2D* root;
    raylib::Window window;
    std::vector<Node2D*> nodes;
    float deltaTime;
    int init();
    void deleteNode(Node2D* node);
    void deleteNodeChildren(Node2D* node);
public:
    App() = delete;
    App(const App&& other) = delete;
    App(uint16_t windowWidth, uint16_t windowHeight, std::string windowName);
    ~App();
    inline Node2D* getRoot() { return root; }
    inline void addChildToRoot(Node2D* child) { root->transform.addChild(child); }
    inline void removeChildFromRoot(Node2D* child) { root->transform.removeChild(child); }
    inline float getDeltaTime() const { return deltaTime; };
    int run();

    template<class T = Node2D, class... Args>
    T* createNode(std::string name = "_noname_", Args&&... args)
    {
        if(std::is_base_of<Node2D, T>::value)
        {
            T* newNode = new T(name, std::forward<Args>(args)...);
            nodes.push_back(newNode);
            return newNode;
        }
        else
        {
            return nullptr;
        }
    }
};

}
#endif // PRIM_APP