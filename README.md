# Mesh Solver

A high-performance C++ circuit simulator for calculating equivalent resistance in large resistive grids. This project demonstrates graph-based data structures, numerical analysis (MNA), and multithreading.

## Key Features

*   **Core Engine**: C++17 implementation for maximum performance.
*   **Numerical Analysis**: Uses Modified Nodal Analysis (MNA) and Gaussian Elimination to solve circuit equations.
*   **Multithreading**: Parallelized matrix construction for handling large grids.
*   **Python Bindings**: Seamless integration with Python using `pybind11`.
*   **Object-Oriented Design**: Clean architecture with `Node`, `Component`, and `Circuit` classes.

## Build Instructions

### Option 1: Using CMake (Recommended)

Requires CMake 3.10+ and a C++ compiler.

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### Option 2: Using MinGW / G++ directly

If you only want to build the C++ CLI and tests without Python bindings:

**Build CLI:**
```bash
g++ -std=c++17 -Iinclude src/main.cpp src/Node.cpp src/Component.cpp src/Circuit.cpp src/Solver.cpp -o mesh_solver_cli.exe
```

**Build Tests:**
```bash
g++ -std=c++17 -Iinclude tests/test_core.cpp src/Node.cpp src/Component.cpp src/Circuit.cpp src/Solver.cpp -o run_tests.exe
```

## Usage

### C++ CLI
Run the compiled executable to simulate the hardcoded demo circuit:
```bash
./mesh_solver_cli.exe
```

### Python API
To use the Python bindings, first install the package:
```bash
pip install .
```

Then you can use it in your Python scripts:
```python
import mesh_solver

# Create circuit
c = mesh_solver.Circuit()
n1 = mesh_solver.Node(0)
n2 = mesh_solver.Node(1)

# Set boundary conditions
n1.setFixed(True); n1.setVoltage(5.0)
n2.setFixed(True); n2.setVoltage(0.0)

c.addNode(n1)
c.addNode(n2)

# Add resistor
c.addComponent(mesh_solver.Resistor(10.0, n1, n2))

# Solve
s = mesh_solver.Solver()
s.solve(c)
```

## Project Structure

*   `src/`: C++ source files (`Solver.cpp`, `Circuit.cpp`, etc.)
*   `include/`: Header files
*   `bindings/`: Pybind11 bindings code
*   `tests/`: C++ and Python tests
