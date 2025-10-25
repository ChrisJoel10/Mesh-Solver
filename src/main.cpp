#include <iostream>
#include "../include/Circuit.h"
#include "../include/Solver.h"
#include "../include/Node.h"
#include "../include/Component.h"

int main() {
    std::cout << "Mesh Solver CLI" << std::endl;
    std::cout << "Running demonstration..." << std::endl;

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
    
    std::cout << "Simulation complete." << std::endl;
    std::cout << "Current through resistor: " << r1->getCurrent() << " A" << std::endl;

    return 0;
}
