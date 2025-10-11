#include "../include/Node.h"

Node::Node(int id) : id(id), voltage(0.0), fixed(false) {}

int Node::getId() const { return id; }

double Node::getVoltage() const { return voltage; }

void Node::setVoltage(double v) { voltage = v; }

bool Node::isFixed() const { return fixed; }

void Node::setFixed(bool f) { fixed = f; }
