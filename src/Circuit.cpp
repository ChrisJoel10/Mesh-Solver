#include "../include/Circuit.h"

Circuit::Circuit() {}

Circuit::~Circuit() {
    for (auto node : nodes) {
        delete node;
    }
    for (auto comp : components) {
        delete comp;
    }
}

void Circuit::addNode(Node* node) {
    nodes.push_back(node);
}

void Circuit::addComponent(Component* component) {
    components.push_back(component);
}

const std::vector<Node*>& Circuit::getNodes() const {
    return nodes;
}

const std::vector<Component*>& Circuit::getComponents() const {
    return components;
}
