# ANANKE SYSTEM ARCHITECTURE

## 1. Mathematical Mechanics
A quantum state of $n$ qubits is a state vector $\lvert \psi \rangle$ in a $2^n$-dimensional Hilbert Space.

### State Vector Representation
We bypass external matrix engines by leveraging `std::vector<std::complex<double>>`.
*   A system of $1$ qubit has a size of $2^1 = 2$.
*   A system of $3$ qubits has a size of $2^3 = 8$.
*   Memory footprint scales exponentially at $2^n \times 16$ bytes (per complex double).

### The Kronecker (Tensor) Product
To scale a local single-qubit gate $U$ (a $2 \times 2$ matrix) to operate on a specific qubit index inside an $n$-qubit global register, `ANANKE` computes the global operator matrix via Kronecker expansions:
$$
\mathcal{O} = I \otimes I \otimes \dots \otimes U \otimes \dots \otimes I
$$
This yields a $2^n \times 2^n$ unitary matrix which is then multiplied by the state vector.

## 2. Pipeline Execution flow
1.  **Ingestion:** The engine reads a native quantum instruction file script (`.ank`).
2.  **Allocation:** Instantiating `QuantumRegister(n)` based on the script header, initializing the state vector to $\lvert 00\dots0 \rangle$.
3.  **Transformation:** Parsing individual gate tokens sequentially to mutate the state vector amplitudes through matrix operators.
4.  **Measurement (Collapse):** Processing measurement instructions to collapse the quantum state vector into a classical binary string output.
