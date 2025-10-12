#pragma once
#include <vector>
#include "Node.h"
#include "Component.h"

class Circuit {
public:
    Circuit();
    ~Circuit();

    void addNode(Node* node);
    void addComponent(Component* component);

    const std::vector<Node*>& getNodes() const;
    const std::vector<Component*>& getComponents() const;

private:
    std::vector<Node*> nodes;
    std::vector<Component*> components;
};
