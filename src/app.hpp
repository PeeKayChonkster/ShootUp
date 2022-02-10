#ifndef PRIM_APP
#define PRIM_APP

#include "node.hpp"
#include "node_library.hpp"
#include <raylib-cpp.hpp>
#include <type_traits>


namespace prim
{
    
class App
{
private:
    Node* root;
    raylib::Window window;
    std::vector<Node*> nodes;
    float deltaTime;
    int init();
    void deleteNode(Node* node);
    void deleteNodeChildren(Node* node);
public:
    App(const App& other) = delete;
    App(uint16_t windowWidth, uint16_t windowHeight, std::string windowName);
    ~App();
    inline Node* getRoot() { return root; }
    inline void addChildToRoot(Node* child) { root->addChild(child); }
    inline void removeChildFromRoot(Node* child) { root->removeChild(child); }
    inline float getDeltaTime() const { return deltaTime; };
    int run();

    template<class T = Node, class... Args>
    T* createNode(std::string name = "_noname_", Args&&... args)
    {
        if(std::is_base_of<Node, T>::value)
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