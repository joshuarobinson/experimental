#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fstream>
#include <iostream>
#include <array>

// Calculate entry over the bytes in a file.
double GetByteEntropy(const std::string& filename)
{
    std::ifstream in_f(filename, std::ifstream::in | std::ifstream::binary);

    if (!in_f) {
        std::cerr << "Error, unable to open input file " << filename << std::endl;
        return 0.0;  // Error condition? This seems awkward.
    }

    const size_t k_domain_bytes = sizeof(uint8_t);
    const size_t k_domain_max = 1 << (k_domain_bytes * 8);

    std::array<int, k_domain_max> byte_counters;
    std::fill(byte_counters.begin(), byte_counters.end(), 0);

    // Now calculate the p(x) probabilities of each possible byte (0-255).
    int total_bytes = 0;
    while (in_f) {
        uint8_t x;
        in_f >> x;

        byte_counters.at(x)++;
        total_bytes++;
    }

    // Now calculate the entropy value.
    double h = 0.0;  // Entropy
    for (const int& byte_counter : byte_counters) {
        // Avoid the inf value returned by log(0.0).
        if (byte_counter > 0) {
            double p_i  = static_cast<double>(byte_counter) / total_bytes;

            h -= p_i * (log(p_i) / log(2.0));
        }
    }

    return h;
}

int main(int argc, char* argv[])
{
    // Check command line arguments.
    if (argc < 2) {
        std::cerr << "Error, program usage: " << argv[0] << " [inputfilenames...]" << std::endl;
        exit(1);
    }

    // Loop over all the command line inputs, open each file and calculate it's entropy.
    for (int argnum = 1; argnum < argc; ++argnum) {
        const std::string filename(argv[argnum]);
        double h = GetByteEntropy(filename);

        // Output our entropy value for the file.
        std::cout << filename << "\t" << h << std::endl;
    }

    return 0;
}