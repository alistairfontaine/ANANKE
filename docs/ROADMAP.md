# ANANKE ROADMAP & SCOPE

## Phase 1: Foundations (Current)
- [x] Zero-dependency system scaffolding
- [x] State vector implementation (`std::complex`)
- [x] Kronecker tensor product calculations
- [x] Basic gate array (Hadamard, Pauli-X)
- [x] Basic Entanglement simulation (Bell State validation)

## Phase 2: Operator Optimizations
- [ ] Implement Phase-Shift ($R_\phi$), Phase (S), and Toffoli (CCNOT) gates.
- [ ] Optimize tensor operations to avoid allocating full $2^n \times 2^n$ matrices in RAM (sparse matrix or direct bit-manipulation mapping).

## Phase 3: Classical Quantum Algorithms
- [ ] Implement Deutsch-Jozsa Algorithm (proving quantum speedup).
- [ ] Implement Grover's Search Algorithm.
- [ ] Implement Quantum Fourier Transform (QFT).
