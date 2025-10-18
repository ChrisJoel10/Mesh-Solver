#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(mesh_solver, m) {
    m.doc() = "Mesh Solver Python Bindings";
}
