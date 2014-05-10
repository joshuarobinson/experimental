"""This script calculates the byte-wise entropy of all files listed on the
    command-line. """

#
# Run as follows:
# > python3 entropy.py *

import math
from collections import Counter
import sys

def get_byte_entropy(filename):
    try:
        with open(filename, "rb") as fil:
            contents = fil.read()
            # Create histogram of each byte value.
            byte_counters = Counter(contents)

            # Calculate entropy.
            entropy = 0.0
            for byte in byte_counters:
                p_i = byte_counters[byte] / len(contents)
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
