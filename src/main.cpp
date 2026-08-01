#include "../include/Ananke.hpp"
#include <iostream>
#include <map>

int main() {
    std::cout << "=========================================" << std::endl;
    std::cout << "   ANANKE: Custom Raw Quantum Engine     " << std::endl;
    std::cout << "=========================================" << std::endl;

    // Instantiating a 2-qubit system
    Ananke::QuantumRegister reg(2);

    std::cout << "Initial state (Pure Ground State):";
    reg.print_state();

    // 1. Put qubit 0 into Superposition using Hadamard gate
    std::cout << "\nApplying Hadamard (H) gate to Qubit 0..." << std::endl;
    reg.apply_gate(Ananke::H(), 0);
    reg.print_state();

    // 2. Entangle Qubit 0 and Qubit 1 using CNOT gate
    std::cout << "\nApplying CNOT (Control: 0, Target: 1)..." << std::endl;
    reg.apply_cnot(0, 1);
    reg.print_state();

    // 3. Run a statistical measurement check across 1000 collapses
    std::cout << "\nRunning 1000 measurements to verify entanglement..." << std::endl;
    std::map<std::string, int> histogram;

    for(int i = 0; i < 1000; ++i) {
        // Re-generate the state for statistical tracking
        Ananke::QuantumRegister test_reg(2);
        test_reg.apply_gate(Ananke::H(), 0);
        test_reg.apply_cnot(0, 1);
        std::string outcome = test_reg.measure();
        histogram[outcome]++;
    }

    std::cout << "\nMeasurement Results Histogram:" << std::endl;
    for (const auto& [state, count] : histogram) {
        std::cout << "State |" << state << "> counted: " << count << " times" << std::endl;
    }

    return 0;
}
