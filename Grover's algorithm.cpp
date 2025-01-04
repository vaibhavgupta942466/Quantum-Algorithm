// Quantum Search Algorithm (Grover's Algorithm)
// Grover's algorithm is a quantum algorithm that finds the solution to an unsorted database search problem with a quadratic speedup over classical algorithms. It is used to search an unsorted database of N items to find a marked item in O(√N) time complexity. The algorithm is based on the principles of quantum superposition and interference.

// The algorithm consists of the following steps:
// 1. Initialize the quantum state to a superposition of all possible states.
// 2. Apply the oracle function to mark the solution state.
// 3. Apply the Grover diffusion operator to amplify the amplitude of the solution state.
// 4. Repeat steps 2 and 3 √N times to increase the probability of measuring the solution state.

// The algorithm is used in various applications such as database search, optimization problems, and cryptography. It is a key quantum algorithm that showcases the power of quantum parallelism and interference.

// Function to apply the Grover diffusion operator to amplify the amplitude of the solution state
void applyGroverDiffusionOperator(QubitRegister& qubits) {
    // Step 1: Apply Hadamard gates to all qubits
    qubits.applyHadamard();

    // Step 2: Apply X gates to all qubits
    qubits.applyPauliX();

    // Step 3: Apply H gates to all qubits
    qubits.applyHadamard();

    // Step 4: Apply Z gates to all qubits
    qubits.applyPauliZ();

    // Step 5: Apply H gates to all qubits
    qubits.applyHadamard();
}

// Function to apply the Grover's algorithm to search for a marked item in an unsorted database
void groversAlgorithm(QubitRegister& qubits, int markedItem) {
    int numQubits = qubits.getNumQubits();
    int numIterations = static_cast<int>(std::round(std::sqrt(numQubits)));

    // Step 1: Initialize the quantum state to a superposition of all possible states
    qubits.applyHadamard();

    // Step 2: Apply the oracle function to mark the solution state
    qubits.applyPauliX(markedItem);
    qubits.applyPauliZ(markedItem);

    // Step 3: Apply Grover diffusion operator √N times
    for (int i = 0; i < numIterations; ++i) {
        applyGroverDiffusionOperator(qubits);
    }
}

int main() {
    // Initialize the quantum register with 4 qubits
    QubitRegister qubits(4);

    // Marked item in the unsorted database
    int markedItem = 6;

    // Apply Grover's algorithm to search for the marked item
    groversAlgorithm(qubits, markedItem);

    // Measure the quantum state to find the marked item
    int measuredItem = qubits.measure();

    // Output the measured item
    std::cout << "Measured Item: " << measuredItem << std::endl;

    return 0;
}