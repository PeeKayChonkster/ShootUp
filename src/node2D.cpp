#include "node2D.hpp"


prim::Node2D::Node2D(std::string name) : Node(name), transform(this) {}

prim::Node2D::~Node2D() {}