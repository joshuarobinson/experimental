#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
#include <iostream>


const int BadFilenameException = 10;

// Calculate entry over the bytes in a file.
double GetByteEntropy(const std::string& filename)
{
    std::ifstream in_f(filename, std::ifstream::in | std::ifstream::binary);

    if (!in_f) {
        throw BadFilenameException;
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

    double h = 0.0;  // Entropy

    // Calculate the entropy with this lambda.
    auto calc_entropy_f = [&](int x) {
        if (x > 0) {
            double p_i  = static_cast<double>(x) / total_bytes;

            h -= p_i * (log(p_i) / log(2.0));
        }
    };

    // Do calculation.
    std::for_each(byte_counters.begin(), byte_counters.end(), calc_entropy_f);

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

        try {
            double h = GetByteEntropy(filename);

            // Output our entropy value for the file.
            std::cout << filename << "\t" << h << std::endl;
        } catch (int i) {
            std::cerr << "Error " << i << ", unable to open input file " << filename << std::endl;
        }
    }

    return 0;
}
