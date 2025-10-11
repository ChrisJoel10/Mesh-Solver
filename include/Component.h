#pragma once
#include "Node.h"

class Component {
public:
    virtual ~Component() = default;
    virtual double getCurrent() const = 0;
};

class Resistor : public Component {
public:
    Resistor(double resistance, Node* n1, Node* n2);
    double getResistance() const;
    Node* getNode1() const;
    Node* getNode2() const;
    double getCurrent() const override;

private:
    double resistance;
    Node* node1;
    Node* node2;
};
