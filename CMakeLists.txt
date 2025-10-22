cmake_minimum_required(VERSION 3.10)
project(MeshSolver)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

# Core library
add_library(mesh_solver_core
    src/Node.cpp
    src/Component.cpp
    src/Circuit.cpp
    src/Solver.cpp
)

# CLI Executable
add_executable(mesh_solver_cli src/main.cpp)
target_link_libraries(mesh_solver_cli mesh_solver_core)

# Pybind11
find_package(pybind11 REQUIRED)
pybind11_add_module(mesh_solver bindings/bindings.cpp)
target_link_libraries(mesh_solver PRIVATE mesh_solver_core)

# Tests
add_executable(run_tests tests/test_core.cpp)
target_link_libraries(run_tests mesh_solver_core)
