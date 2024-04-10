#include "FFTSolver.h"
#include "complex"
#include "vector"
#include "iostream"

using std::cout;

void FFTSolver::FFT() {
   cout << "he\n";
}

size_t nearestPower2(size_t N) {
    if (N == 1) return 1;
    size_t res = 2;
    while ((N = N >> 1) != 1) res = res << 1;
    return res;
}
