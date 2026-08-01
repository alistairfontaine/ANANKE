# ANANKE SYSTEM ARCHITECTURE

## 1. Mathematical Mechanics
A quantum state of $n$ qubits is a state vector $\lvert \psi \rangle$ in a $2^n$-dimensional Hilbert Space.

### In-Place Bitwise Amplitude Mutation
To avoid constructing massive $2^n \times 2^n$ dense matrices for simple single-qubit transformations, `ANANKE` maps 2x2 complex unitary operations directly onto state vector pairs using bitwise offset masks:
```cpp
int target_shift = num_qubits - 1 - target;
size_t chunk_size = 1 << target_shift;
// Iterates through indices pairing states separated by the target bit configuration
size_t i0 = i + j;
size_t i1 = i0 + chunk_size;
```
This reduces structural processing complexity from $\mathcal{O}(4^n)$ down to $\mathcal{O}(2^n)$ runtime steps with zero auxiliary heap space overhead.

### Grover Amplitude Inversion
The diffusion operator reflects all active quantum states around the global mean value:
$$
\lvert \psi_{next} \rangle = 2\mu - \lvert \psi_{current} \rangle
$$
Where $\mu$ is the computed complex average amplitude across the entire register.
