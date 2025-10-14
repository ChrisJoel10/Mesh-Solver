#include "../include/Solver.h"
#include <iostream>

void Solver::solve(Circuit& circuit) {
    auto nodes = circuit.getNodes();
    int n = nodes.size();
    
    // Simple MNA for resistive network
    // G * V = I
    std::vector<std::vector<double>> G(n, std::vector<double>(n, 0.0));
    std::vector<double> I(n, 0.0);

    for (auto comp : circuit.getComponents()) {
        Resistor* r = dynamic_cast<Resistor*>(comp);
        if (r) {
            int u = r->getNode1()->getId();
            int v = r->getNode2()->getId();
            double g = 1.0 / r->getResistance();

            if (u < n && v < n) {
                G[u][u] += g;
                G[v][v] += g;
                G[u][v] -= g;
                G[v][u] -= g;
            }
        }
    }

    // Handle fixed nodes (boundary conditions)
    // For fixed nodes, we modify the equation to trivial V_k = known_voltage
    for (int i = 0; i < n; ++i) {
        if (nodes[i]->isFixed()) {
            for (int j = 0; j < n; ++j) {
                G[i][j] = 0.0;
            }
            G[i][i] = 1.0;
            I[i] = nodes[i]->getVoltage();
        }
    }
    
    std::cout << "MNA Matrix constructed." << std::endl;
}
