#include "../include/Ananke.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>

void run_script(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "[-] Error: Could not open script file: " << filepath << std::endl;
        return;
    }

    std::unique_ptr<Ananke::QuantumRegister> reg = nullptr;
    std::string line;

    std::cout << "[+] Parsing ANANKE Execution Script: " << filepath << std::endl;

    while (std::getline(file, line)) {
        // Strip whitespace and skip comments
        if (line.empty() || line[0] == '#') continue;

        std::stringstream ss(line);
        std::string command;
        ss >> command;

        if (command == "qubits") {
            int num_qubits;
            ss >> num_qubits;
            reg = std::make_unique<Ananke::QuantumRegister>(num_qubits);
            std::cout << "[*] Allocated Register with " << num_qubits << " qubits." << std::endl;
        } else if (command == "gate") {
            if (!reg) {
                std::cerr << "[-] Error: Qubit allocation must happen before gate calls." << std::endl;
                return;
            }
            std::string gate_type;
            int target;
            ss >> gate_type >> target;

            if (gate_type == "H") {
                reg->apply_gate(Ananke::H(), target);
                std::cout << "[*] Executed Hadamard (H) on qubit " << target << std::endl;
            } else if (gate_type == "X") {
                reg->apply_gate(Ananke::X(), target);
                std::cout << "[*] Executed Pauli-X (NOT) on qubit " << target << std::endl;
            } else if (gate_type == "R") {
                double phase_angle;
                ss >> phase_angle;
                Ananke::Matrix R_gate = {
                    {Ananke::ONE, Ananke::ZERO},
                    {Ananke::ZERO, std::exp(Ananke::Complex(0.0, phase_angle))}
                };
                reg->apply_gate(R_gate, target);
                std::cout << "[*] Executed Phase-Shift R(" << phase_angle << " rad) on qubit " << target << std::endl;
            }
        }
            else if (command == "cnot") {
            if (!reg) return;
            int control, target;
            ss >> control >> target;
            reg->apply_cnot(control, target);
            std::cout << "[*] Executed CNOT (Control: " << control << ", Target: " << target << ")" << std::endl;
        } else if (command == "measure") {
            if (!reg) return;
            reg->print_state();
            std::string result = reg->measure();
            std::cout << "\n[+] State Collapsed! Final Measurement Result: |" << result << ">" << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    std::cout << "=========================================" << std::endl;
    std::cout << "   ANANKE: Custom Raw Quantum Engine     " << std::endl;
    std::cout << "=========================================" << std::endl;

    if (argc < 2) {
        std::cout << "[-] Usage: ./ananke_sim <script_file.ank>" << std::endl;
        return 1;
    }

    run_script(argv[1]);
    return 0;
}
