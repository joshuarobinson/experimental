import math
from collections import Counter

def GetByteEntropy(filename):
    with open(filename) as f:
        contents = f.read()
        byte_counters = Counter(contents)

        h = 0.0
        for b in byte_counters:
            c = byte_counters[b]
            p_i = c / len(contents)
            h -= p_i * math.log(p_i, 2)

        return h

    return None

def main():
    f = "Makefile"
    print("{}\t{}".format(f, GetByteEntropy(f)))

if __name__ == '__main__':
    main()
