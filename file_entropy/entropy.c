#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define ERR_BADFILENAME (10)
#define DOMAIN_MAX      (1 << 8)

// Calculate entry over the bytes in a file.
//
// Return non-zero if there was an error.
int get_byte_entropy(const char * filename, double * answer)
{
    FILE* fp = fopen(filename, "rb");

    if (!fp) {
        return ERR_BADFILENAME;
    }

    int byte_counters[DOMAIN_MAX];
    for (int i = 0; i < DOMAIN_MAX; ++i) {
        byte_counters[i] = 0;
    }

    // Now calculate the p(x) probabilities of each possible byte (0-255).
    int total_bytes = 0;
    unsigned char x;
    while (fread(&x, 1, 1, fp)) {
        byte_counters[x]++;
        total_bytes++;
    }
    fclose(fp);

    // Now calculate the entropy value.
    double h = 0.0;  // Entropy
    for (int i = 0; i < DOMAIN_MAX; ++i) {
        // Avoid the inf value returned by log(0.0).
        if (byte_counters[i] > 0) {
            double p_i  = (double)byte_counters[i] / total_bytes;

            h -= p_i * (log(p_i) / log(2.0));
        }
    }

    *answer = h;
    return 0;  // Sucess.
}

int main(int argc, char* argv[])
{
    // Check command line arguments.
    if (argc < 2) {
        fprintf(stderr, "Error, program usage: %s [inputfilenames...]\n", argv[0]);
        exit(1);
    }

    // Loop over all the command line inputs, open each file and calculate it's entropy.
    for (int argnum = 1; argnum < argc; ++argnum) {
        double h;

        int e;  // For return code.
        if ((e = get_byte_entropy(argv[argnum], &h))) {
            fprintf(stderr, "Error %d, unable to open input file %s\n", e, argv[argnum]);
        } else {
            // Output our entropy value for the file.
            printf("%s\t%g\n", argv[argnum], h);
        }
    }

    return 0;
}
