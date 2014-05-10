"""This script calculates the byte-wise entropy of all files listed on the
    command-line -- uses numpy library. """

#
# Run as follows:
# > python entropy_numpy.py *

import numpy as np
import math
import sys

def get_byte_entropy(filename):
    try:
        raw_data = np.fromfile(filename, dtype=np.uint8)

        # Create histogram of each byte value.
        # density=True converts to probabilities for us.
        (p_vals, __) = byte_counters = np.histogram(
                raw_data, bins=range(256), density=True)

        # Calculate entropy.
        entropy = 0.0
        for p_i in p_vals[np.nonzero(p_vals)]:
            entropy -= p_i * math.log(p_i, 2)

        return round(entropy, 5)  # Round to five decimal places.

    except EnvironmentError:  # If file didn't open or doesn't exist.
        return None


def main():
    # Loop over each argv (except the first, which is the program's name).
    for filename in sys.argv[1:]:
        entropy = get_byte_entropy(filename)
        if entropy:
            print("{}\t{}".format(filename, entropy))


if __name__ == '__main__':
    main()
