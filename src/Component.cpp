#include "../include/Component.h"
#include <cmath>

Resistor::Resistor(double resistance, Node* n1, Node* n2)
    : resistance(resistance), node1(n1), node2(n2) {}

double Resistor::getResistance() const { return resistance; }
Node* Resistor::getNode1() const { return node1; }
Node* Resistor::getNode2() const { return node2; }

double Resistor::getCurrent() const {
    return (node1->getVoltage() - node2->getVoltage()) / resistance;
}
