#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../include/Node.h"
#include "../include/Component.h"
#include "../include/Circuit.h"

namespace py = pybind11;

PYBIND11_MODULE(mesh_solver, m) {
    m.doc() = "Mesh Solver Python Bindings";

    py::class_<Node>(m, "Node")
        .def(py::init<int>())
        .def("getId", &Node::getId)
        .def("getVoltage", &Node::getVoltage)
        .def("setVoltage", &Node::setVoltage)
        .def("isFixed", &Node::isFixed)
        .def("setFixed", &Node::setFixed);

    py::class_<Component>(m, "Component");

    py::class_<Resistor, Component>(m, "Resistor")
        .def(py::init<double, Node*, Node*>())
        .def("getResistance", &Resistor::getResistance)
        .def("getCurrent", &Resistor::getCurrent);

    py::class_<Circuit>(m, "Circuit")
        .def(py::init<>())
        .def("addNode", &Circuit::addNode)
        .def("addComponent", &Circuit::addComponent)
        .def("getNodes", &Circuit::getNodes)
        .def("getComponents", &Circuit::getComponents);
}
