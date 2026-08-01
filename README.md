# ANANKE

<p align="center">
  <img src="assets/banner.png" alt="ANANKE Quantum Banner" width="100%">
</p>

A pure, zero-dependency, high-utility Quantum Computing Simulator platform built entirely from scratch in C++17.

## The Philosophy
No massive frameworks. No enterprise bloat. No third-party matrix libraries. `ANANKE` rejects dependency addiction to prove that advanced computational paradigms can be simulated directly on consumer hardware using raw mathematics, clear bitwise logic, and optimized C++17 standards.

## Production Capabilities
*   **Bitwise Optimization:** Bypasses tensor matrix allocations via zero-RAM in-place state mutations.
*   **Custom Script Runtime:** Reads and interprets standalone quantum instructions via native `.ank` files.
*   **Algorithmic Verification:** Ships out-of-the-box with functional executions for Bell State Entanglement, Deutsch-Jozsa Speedups, and Grover's Amplitude Search.

## Getting Started
```bash
g++ -O3 -std=c++17 src/main.cpp -o ananke_sim
./ananke_sim scripts/grover_search.ank
```
