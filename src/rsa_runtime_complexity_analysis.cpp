#include <algorithm>
#include <iostream>
#include <chrono>
#include <vector>
#include <sstream>
#include <iomanip> // For JSON formatting
#include <fstream> // For writing JSON to file
#include "rsa.h"   // Include your updated RSA library

// Function to compute the median of a vector
double ComputeMedian(std::vector<double>& runtimes) {
    std::sort(runtimes.begin(), runtimes.end());
    size_t size = runtimes.size();
    if (size % 2 == 0) {
        return (runtimes[size / 2 - 1] + runtimes[size / 2]) / 2.0; // Average of middle two
    } else {
        return runtimes[size / 2]; // Middle element
    }
}

// RSA runtime analysis function
void AnalyzeTimeComplexity() {
    // Define the key sizes as powers of 2 (from 512 to 16,384 bits)
    std::vector<int> key_sizes = {512, 1024, 2048, 4096, 8192, 16384};

    // Store runtime results for each key size
    std::vector<double> medians;

    // Measure runtime for each key size
    for (int bits : key_sizes) {
        std::cout << "Measuring for " << bits << " bits...\n";
        int num_trials = 10; // Run each key size 10 times
        std::vector<double> runtimes;

        for (int trial = 0; trial < num_trials; ++trial) {
            auto start = std::chrono::high_resolution_clock::now();

            try {
                // Generate RSA key pair using the updated function
                auto key_pair = rsa_app::GenerateKeyPair(bits);
            } catch (const std::exception& e) {
                std::cerr << "Failed to generate keys for " << bits << " bits: " << e.what() << std::endl;
                runtimes.push_back(-1.0); // Mark a failed run
                continue;
            }

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            runtimes.push_back(elapsed.count()); // Record runtime
        }

        // Compute the median runtime
        if (!runtimes.empty() && *std::max_element(runtimes.begin(), runtimes.end()) > 0) {
            medians.push_back(ComputeMedian(runtimes));
        } else {
            medians.push_back(-1.0); // Use -1.0 if all runs failed
        }
    }

    // Generate JSON results and write them to a file
    std::ostringstream json_output;
    json_output << "{\n  \"time_complexity\": [\n";

    for (size_t i = 0; i < key_sizes.size(); ++i) {
        json_output << "    { \"key_size\": " << key_sizes[i]
                    << ", \"median_runtime\": " << std::fixed << std::setprecision(6) << medians[i] << " }";
        if (i != key_sizes.size() - 1) {
            json_output << ",\n";
        }
    }

    json_output << "\n  ]\n}";

    // Print results to console
    std::cout << json_output.str() << std::endl;

    // Save to a file
    std::ofstream file("rsa_runtime.json");
    if (file.is_open()) {
        file << json_output.str();
        file.close();
        std::cout << "\nJSON file successfully written to rsa_runtime.json\n";
    } else {
        std::cerr << "\nFailed to write JSON file.\n";
    }
}

int main() {
    std::cout << "Starting RSA runtime analysis...\n";
    AnalyzeTimeComplexity();
    std::cout << "Analysis complete.\n";
    return 0;
}