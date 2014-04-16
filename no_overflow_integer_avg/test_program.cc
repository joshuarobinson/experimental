#include <assert.h>
#include <climits>
#include <iostream>

// Templated version of a no-overflow average of two integer types.
template <typename T>
T average_without_overflow(T x, T y) {
	return (x & y) + ((x ^ y) / 2);
}

int main(int argc, char ** argv) {

	// First attempt will overflow!

	int val1 = INT_MAX - 5000;  // Suitably big number, close to limits.
	int val2 = val1 + 2;

	int avg = (val1 + val2) / 2;

	assert(avg != val1 + 1);
	std::cout << "Average didn't compute correctly." << std::endl;

	// Second attempt, this time without an overflow.
	int avg2 = average_without_overflow(val1, val2);
	assert(avg2 == val1 + 1);
	std::cout << "Successfully avoided an overflow!" << std::endl;

	return 0;
}
