#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// Core Shor's Algorithm Implementation
// This program demonstrates a simulation of Shor's Algorithm to factorize a given integer N.
// Shor's Algorithm is a quantum algorithm that can factorize integers in polynomial time.
// The algorithm is probabilistic and requires a quantum computer to run efficiently.
// This simulation uses classical computation to demonstrate the key steps of Shor's Algorithm.
// The algorithm is based on the principles of number theory and quantum computation.
// The algorithm consists of the following steps:

// Core Shor's Algorithm used Furier Transform and Quantum Fourier Transform to find the period of a function.:
// 1. Select a random integer 'a' between 1 and N-1.
// 2. Compute the greatest common divisor (GCD) of 'a' and N.
// 3. If the GCD is greater than 1, we've found a nontrivial factor of N.
// 4. Otherwise, find the order 'r' of 'a' modulo N (smallest 'r' such that a^r ≡ 1 (mod N)).
// 5. If 'r' is even, proceed to find factors using the order 'r'.
// 6. Try to find factors using the order 'r' (even order is a key factor here).
// 7. If a factor is found, it is a nontrivial factor of N.

// Function to compute the greatest common divisor (GCD) of two integers using the Euclidean algorithm
int computeGCD(int a, int b) {
    cout << "Computing GCD of " << a << " and " << b << endl;
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    cout << "GCD is " << a << endl;
    return a;
}

// Function to compute a^b mod n (modular exponentiation) efficiently using exponentiation by squaring
int modularExponentiation(int base, int exponent, int modulus) {
    int result = 1;
    base = base % modulus;  // In case base is greater than modulus

    while (exponent > 0) {
        if (exponent % 2 == 1) {  // If exponent is odd
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;  // Square the base
        exponent = exponent / 2;  // Integer division by 2
    }
    return result;
}

// Function to attempt to find a nontrivial factor of N using Shor's Algorithm
int findNonTrivialFactor(int N) {
    srand(time(0));  // Seed the random number generator for picking a random 'a'

    // Step 1: Select a random integer 'a' between 1 and N-1
    int randomIntegerA = rand() % (N - 1) + 1;

    // Step 2: Compute the greatest common divisor (GCD) of a and N
    int gcdValue = computeGCD(randomIntegerA, N);

    // If the GCD is greater than 1, we've found a nontrivial factor (return it)
    if (gcdValue > 1) {
        return gcdValue;
    }

    // Step 3: We must now find the order 'r' of 'a' modulo N (the smallest 'r' such that a^r ≡ 1 (mod N))
    // This requires a brute-force search for the smallest 'r' such that a^r % N == 1
    int orderR = 0;
    for (int i = 1; i <= N; ++i) {
        if (modularExponentiation(randomIntegerA, i, N) == 1) {
            orderR = i;
            break;
        }
    }

    // If 'r' is even, proceed to find factors using the order 'r'
    if (orderR % 2 == 0) {
        // Step 4: Try to find factors using the order 'r' (even order is a key factor here)
        int factor1 = computeGCD(modularExponentiation(randomIntegerA, orderR / 2, N) - 1, N);
        int factor2 = computeGCD(modularExponentiation(randomIntegerA, orderR / 2, N) + 1, N);

        // If either factor is non-trivial and smaller than N, return it
        if (factor1 > 1 && factor1 < N) {
            return factor1;
        }
        if (factor2 > 1 && factor2 < N) {
            return factor2;
        }
    }

    // If no factor was found, return -1 (indicating failure)
    return -1;
}

int main() {
    int numberToFactor;
    cout << "Enter an integer to factor (N): ";
    cin >> numberToFactor;

    // Call the function to attempt to find a nontrivial factor of the number
    int factor = findNonTrivialFactor(numberToFactor);

    if (factor != -1) {
        cout << "A nontrivial factor of " << numberToFactor << " is " << factor << endl;
    } else {
        cout << "Failed to find a factor of " << numberToFactor << "." << endl;
    }

    return 0;
}
