/***
 *
 *
 * Test CPP execution time
 */

#include <chrono>

int main(int argc, const char *argv[]) {

	auto start = std::chrono::high_resolution_clock::now();

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	printf("Time taken: (%.0f μs) (%.6f ms) (%.6f sec)\n", (float) duration.count(), (float) (duration.count() / 1000.0), (float) (duration.count() / 1000000.0));

	return 0;
}

