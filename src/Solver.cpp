#include "../include/Solver.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

void Solver::solve(Circuit& circuit) {
    const auto& nodes = circuit.getNodes();
    int n = nodes.size();
    
    // Simple MNA for resistive network
    // G * V = I
    std::vector<std::vector<double>> G(n, std::vector<double>(n, 0.0));
    std::vector<double> I(n, 0.0);

    // Check for threading support (common issue on MinGW)
#if defined(_GLIBCXX_HAS_GTHREADS) && defined(_GLIBCXX_USE_C99_STDINT_TR1)
    std::mutex mtx;
    const auto& components = circuit.getComponents();
    size_t num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) num_threads = 2;
    std::vector<std::thread> threads;
    threads.reserve(num_threads);

    auto worker = [&](size_t start, size_t end) {
        for (size_t i = start; i < end; ++i) {
            Resistor* r = dynamic_cast<Resistor*>(components[i]);
            if (r) {
                int u = r->getNode1()->getId();
                int v = r->getNode2()->getId();
                double g = 1.0 / r->getResistance();

                if (u < n && v < n) {
                    std::lock_guard<std::mutex> lock(mtx);
                    G[u][u] += g;
                    G[v][v] += g;
                    G[u][v] -= g;
                    G[v][u] -= g;
                }
            }
        }
    };

    size_t chunk_size = components.size() / num_threads;
    for (size_t i = 0; i < num_threads; ++i) {
        size_t start = i * chunk_size;
        size_t end = (i == num_threads - 1) ? components.size() : (i + 1) * chunk_size;
        threads.emplace_back(worker, start, end);
    }

    for (auto& t : threads) {
        t.join();
    }
#else
    // Single-threaded fallback for environments without std::thread (e.g., some MinGW setups)
    std::cout << "Threading not supported, running single-threaded." << std::endl;
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
#endif

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
    
    std::cout << "MNA Matrix constructed. Solving..." << std::endl;

    // Gaussian Elimination
    for (int i = 0; i < n; ++i) {
        // Pivot
        int pivot = i;
        for (int j = i + 1; j < n; ++j) {
            if (std::abs(G[j][i]) > std::abs(G[pivot][i])) {
                pivot = j;
            }
        }
        if (std::abs(G[pivot][i]) < 1e-9) {
            std::cerr << "Error: Singular matrix, cannot solve." << std::endl;
            return;
        }
        std::swap(G[i], G[pivot]);
        std::swap(I[i], I[pivot]);

        // Eliminate
        for (int j = i + 1; j < n; ++j) {
            double factor = G[j][i] / G[i][i];
            for (int k = i; k < n; ++k) {
                G[j][k] -= factor * G[i][k];
            }
            I[j] -= factor * I[i];
        }
    }

    // Back Substitution
    std::vector<double> solution(n);
    for (int i = n - 1; i >= 0; --i) {
        double sum = 0.0;
        for (int j = i + 1; j < n; ++j) {
            sum += G[i][j] * solution[j];
        }
        solution[i] = (I[i] - sum) / G[i][i];
        nodes[i]->setVoltage(solution[i]);
    }

    std::cout << "Circuit solved." << std::endl;
}
