import sys
import os

# Ensure we can import the built module (assuming it's in build/ or similar)
# For this test script, we might need to adjust PYTHONPATH or install the module first.
# Here we assume 'mesh_solver' is importable.

try:
    import mesh_solver
except ImportError:
    print("Error: mesh_solver module not found. Make sure to build and install it first.")
    sys.exit(1)

def test_simple_circuit():
    print("Testing simple circuit...")
    c = mesh_solver.Circuit()
    n1 = mesh_solver.Node(0)
    n2 = mesh_solver.Node(1)
    
    n1.setFixed(True)
    n1.setVoltage(5.0)
    n2.setFixed(True)
    n2.setVoltage(0.0)
    
    c.addNode(n1)
    c.addNode(n2)
    
    r1 = mesh_solver.Resistor(10.0, n1, n2)
    c.addComponent(r1)
    
    s = mesh_solver.Solver()
    s.solve(c)
    
    # Current should be V/R = 5/10 = 0.5
    current = r1.getCurrent()
    assert abs(current - 0.5) < 1e-6, f"Expected 0.5, got {current}"
    print("Simple circuit passed.")

def test_series_circuit():
    print("Testing series circuit...")
    c = mesh_solver.Circuit()
    n1 = mesh_solver.Node(0)
    n2 = mesh_solver.Node(1)
    n3 = mesh_solver.Node(2)
    
    n1.setFixed(True)
    n1.setVoltage(10.0)
    n3.setFixed(True)
    n3.setVoltage(0.0)
    
    c.addNode(n1)
    c.addNode(n2)
    c.addNode(n3)
    
    # R1=10, R2=10. Total R=20. I = 10/20 = 0.5A.
    # V_n2 = 10 - I*R1 = 10 - 0.5*10 = 5V.
    
    r1 = mesh_solver.Resistor(10.0, n1, n2)
    r2 = mesh_solver.Resistor(10.0, n2, n3)
    
    c.addComponent(r1)
    c.addComponent(r2)
    
    s = mesh_solver.Solver()
    s.solve(c)
    
    assert abs(n2.getVoltage() - 5.0) < 1e-6, f"Expected 5.0V at n2, got {n2.getVoltage()}"
    print("Series circuit passed.")

if __name__ == "__main__":
    test_simple_circuit()
    test_series_circuit()
    print("All Python integration tests passed.")
