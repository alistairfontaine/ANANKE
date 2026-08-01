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

        Matrix tensor_product(const Matrix& A, const Matrix& B) {
            size_t rA = A.size(), cA = A[0].size();
            size_t rB = B.size(), cB = B[0].size();
            Matrix result(rA * rB, std::vector<Complex>(cA * cB, ZERO));

            for (size_t i = 0; i < rA; ++i) {
                for (size_t j = 0; j < cA; ++j) {
                    for (size_t k = 0; k < rB; ++k) {
                        for (size_t l = 0; l < cB; ++l) {
                            result[i * rB + k][j * cB + l] = A[i][j] * B[k][l];
                        }
                    }
                }
            }
            return result;
        }

    public:
        QuantumRegister(int qubits) : num_qubits(qubits) {
            size_t dim = 1 << qubits;
            state.assign(dim, ZERO);
            state[0] = ONE;
        }

        void apply_gate(const Matrix& gate, int target) {
            Matrix I = {{ONE, ZERO}, {ZERO, ONE}};
            Matrix full_operator;

            if (target == 0) {
                full_operator = gate;
            } else {
                full_operator = I;
            }

            for (int i = 1; i < num_qubits; ++i) {
                if (i == target) {
                    full_operator = tensor_product(full_operator, gate);
                } else {
                    full_operator = tensor_product(full_operator, I);
                }
            }

            size_t dim = 1 << num_qubits;
            StateVector next_state(dim, ZERO);
            for (size_t i = 0; i < dim; ++i) {
                for (size_t j = 0; j < dim; ++j) {
                    next_state[i] += full_operator[i][j] * state[j];
                }
            }
            state = next_state;
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
