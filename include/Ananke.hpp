#ifndef ANANKE_HPP
#define ANANKE_HPP

#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <random>
#include <string>
#include <iomanip>

namespace Ananke {

    using Complex = std::complex<double>;
    using StateVector = std::vector<Complex>;
    using Matrix = std::vector<std::vector<Complex>>;

    const Complex ZERO(0.0, 0.0);
    const Complex ONE(1.0, 0.0);
    const Complex ISQRT2(1.0 / std::sqrt(2.0), 0.0);

    class QuantumRegister {
    private:
        int num_qubits;
        StateVector state;

    public:
        QuantumRegister(int qubits) : num_qubits(qubits) {
            size_t dim = 1 << qubits;
            state.assign(dim, ZERO);
            state[0] = ONE; // Initialize to ground state |00...0>
        }

        // Blazing-fast In-Place Bitwise Gate Application (Zero RAM Allocations)
        void apply_gate(const Matrix& gate, int target) {
            size_t dim = 1 << num_qubits;
            int target_shift = num_qubits - 1 - target;
            size_t chunk_size = 1 << target_shift;

            for (size_t i = 0; i < dim; i += (chunk_size << 1)) {
                for (size_t j = 0; j < chunk_size; ++j) {
                    size_t i0 = i + j;
                    size_t i1 = i0 + chunk_size;

                    Complex c0 = state[i0];
                    Complex c1 = state[i1];

                    // Explicit 2x2 Matrix-Vector dot product logic without external dependencies
                    state[i0] = gate[0][0] * c0 + gate[0][1] * c1;
                    state[i1] = gate[1][0] * c0 + gate[1][1] * c1;
                }
            }
        }

        void apply_cnot(int control, int target) {
            size_t dim = 1 << num_qubits;
            StateVector next_state = state;

            for (size_t i = 0; i < dim; ++i) {
                if ((i & (1 << (num_qubits - 1 - control))) != 0) {
                    size_t target_mask = 1 << (num_qubits - 1 - target);
                    size_t flipped_index = i ^ target_mask;
                    next_state[flipped_index] = state[i];
                }
            }
            state = next_state;
        }

        // Grover Diffusion Operator: In-place inversion about the mean (Zero Allocations)
        void apply_diffusion() {
            size_t dim = 1 << num_qubits;
            Complex sum(0.0, 0.0);

            for (size_t i = 0; i < dim; ++i) {
                sum += state[i];
            }

            Complex mean = sum / static_cast<double>(dim);

            for (size_t i = 0; i < dim; ++i) {
                state[i] = 2.0 * mean - state[i];
            }
        }

        // Target Phase Inversion for multi-qubit search scripts
        void apply_phase_flip(size_t target_index) {
            if (target_index < state.size()) {
                state[target_index] = -state[target_index];
            }
        }

        std::string measure() {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis(0.0, 1.0);
            double r = dis(gen);

            double cumulative_probability = 0.0;
            size_t selected_state = 0;

            for (size_t i = 0; i < state.size(); ++i) {
                cumulative_probability += std::norm(state[i]);
                if (r <= cumulative_probability) {
                    selected_state = i;
                    break;
                }
            }

            state.assign(state.size(), ZERO);
            state[selected_state] = ONE;

            std::string binary = "";
            for (int i = num_qubits - 1; i >= 0; --i) {
                binary += ((selected_state >> i) & 1) ? "1" : "0";
            }
            return binary;
        }

        void print_state() const {
            std::cout << "\n--- Current Quantum State Vector ---" << std::endl;
            for (size_t i = 0; i < state.size(); ++i) {
                if (std::norm(state[i]) > 1e-6) {
                    std::cout << "|";
                    for (int q = num_qubits - 1; q >= 0; --q) {
                        std::cout << ((i >> q) & 1);
                    }
                    std::cout << ">: " << std::fixed << std::setprecision(4)
                              << state[i] << " | Prob: " << std::norm(state[i]) * 100 << "%" << std::endl;
                }
            }
        }
    };

    inline Matrix H() {
        return {{ISQRT2, ISQRT2}, {ISQRT2, -ISQRT2}};
    }

    inline Matrix X() {
        return {{ZERO, ONE}, {ONE, ZERO}};
    }

} // namespace Ananke

#endif // ANANKE_HPP
