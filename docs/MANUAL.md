# ANANKE USER MANUAL

## Compilation
Compile the project natively using `g++`:
```bash
g++ -O3 -std=c++17 src/main.cpp -o ananke_sim
```

## Basic API Usage

### 1. Creating a Register
```cpp
// Instantiate a register with 3 qubits (dimension 8)
Ananke::QuantumRegister reg(3);
```

### 2. Mutating States
```cpp
// Apply Hadamard to qubit 0 to put it into superposition
reg.apply_gate(Ananke::H(), 0);

// Entangle qubit 0 (control) with qubit 1 (target)
reg.apply_cnot(0, 1);
```

### 3. Debugging and Measurement
```cpp
// Print out all active states with probabilities > 0%
reg.print_state();

// Collapse the state vector and capture the classical result
std::string outcome = reg.measure();
```
