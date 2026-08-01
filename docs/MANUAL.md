# ANANKE USER MANUAL

## Compilation
Compile the project natively using `g++`:
```bash
g++ -O3 -std=c++17 src/main.cpp -o ananke_sim
```

## Native Code Execution (.ank)

`ANANKE` reads and processes custom quantum scripts using the `.ank` file extension. The script layouts use deterministic token commands per line:

```text
qubits 2
gate H 0
cnot 0 1
measure
```

### Running a Native Script File
```bash
g++ -O3 -std=c++17 src/main.cpp -o ananke_sim
./ananke_sim scripts/bell_state.ank
```
