#include <iostream>
#include <cassert>
#include <cmath>
#include "../include/Circuit.h"
#include "../include/Solver.h"

void test_simple_circuit() {
    Circuit circuit;
    Node* n1 = new Node(0);
    Node* n2 = new Node(1);
    
    n1->setFixed(true);
    n1->setVoltage(10.0);
    
    n2->setFixed(true);
    n2->setVoltage(0.0);
    
    circuit.addNode(n1);
    circuit.addNode(n2);
    
    Resistor* r1 = new Resistor(100.0, n1, n2);
    circuit.addComponent(r1);
    
    Solver solver;
    solver.solve(circuit);
    
    // For a simple fixed node circuit, voltages shouldn't change
    assert(std::abs(n1->getVoltage() - 10.0) < 1e-6);
    assert(std::abs(n2->getVoltage() - 0.0) < 1e-6);
    
    std::cout << "test_simple_circuit passed." << std::endl;
}

void test_voltage_divider() {
    Circuit circuit;
    Node* n1 = new Node(0);
    Node* n2 = new Node(1);
    Node* n3 = new Node(2);
    
    n1->setFixed(true);
    n1->setVoltage(10.0);
    
    n3->setFixed(true);
    n3->setVoltage(0.0);
    
    circuit.addNode(n1);
    circuit.addNode(n2);
    circuit.addNode(n3);
    
    // R1 between n1 and n2 (100 ohm)
    // R2 between n2 and n3 (100 ohm)
    // V_n2 should be 5.0V
    
    circuit.addComponent(new Resistor(100.0, n1, n2));
    circuit.addComponent(new Resistor(100.0, n2, n3));
    
    Solver solver;
    solver.solve(circuit);
    
    assert(std::abs(n2->getVoltage() - 5.0) < 1e-6);
    
    std::cout << "test_voltage_divider passed." << std::endl;
}

int main() {
    test_simple_circuit();
    test_voltage_divider();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
