#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
#include <iostream>


const int BadFilenameException = 10;

// Calculate entropy over the bytes in a file.
double GetByteEntropy(const std::string& filename)
{
    // Open the file with the pointer at the end (ate).
    std::ifstream in_f(filename, std::ifstream::in | std::ifstream::binary | std::ifstream::ate);

    if (!in_f) {
        throw BadFilenameException;
    }

    // Determine file size.
    size_t fsize = in_f.tellg();
    std::vector<char> raw_data(fsize);

    // Read in file contents.
    in_f.seekg(0, std::ios::beg);
    in_f.read(raw_data.data(), fsize);
    in_f.close();

    // Convert to a histogram.
    std::array<int, 256> byte_counters;
    std::fill(byte_counters.begin(), byte_counters.end(), 0);

    std::for_each(raw_data.begin(), raw_data.end(),
            [&byte_counters](char x) { byte_counters.at(x)++; });

    int total_bytes = std::accumulate(byte_counters.begin(), byte_counters.end(), 0);

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
