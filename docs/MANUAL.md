# ANANKE USER MANUAL

## Native Language Specification (.ank)

`ANANKE` executes scripts sequentially line-by-line using individual instruction primitives.

### Supported Token Operations
*   `qubits <integer>`: Dynamically instantiates the register memory space to size $2^n$. Must be the first active command.
*   `gate H <target>`: Applies a Hadamard rotation to the specified target qubit index.
*   `gate X <target>`: Executes a Pauli-X bit flip (quantum NOT) on the target index.
*   `cnot <control> <target>`: Performs a conditional inversion on the target qubit if the control bit is active.
*   `oracle constant` / `oracle balanced`: Executes specialized black-box function paths for Deutsch-Jozsa evaluations.
*   `oracle search`: Marks state $\lvert 11 \rangle$ via an in-place phase-flip for search scripts.
*   `diffusion`: Executes an inversion-about-the-mean step to amplify probabilities.
*   `measure`: Collapses the register wave-function and prints the final binary state string.

### Compilation & Pipeline Run
```bash
g++ -O3 -std=c++17 src/main.cpp -o ananke_sim
./ananke_sim scripts/grover_search.ank
```
