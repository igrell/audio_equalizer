#include "FFTSolver.h"
#include "complex"
#include "vector"
#include "iostream"
#include "NonPower2Exception.h"
#include "numeric"
#include "format"

using std::cout;
typedef long double ldouble;

size_t nearestPower2(size_t N) {
    if (N == 1) return 1;
    size_t res = 2;
    while ((N = N >> 1) != 1) res = res << 1;
    return res;
}

bool isPower2(const size_t& N) {
    return (N > 0 && ((N & (N - 1)) == 0));
}

void bitSwap(vector<size_t> &vec) {
    auto &&N = vec.size();
    for (size_t i = 0 ; i < (N / 2) ; ++i) std::swap(vec[i], vec[N - 1 - i]);
}

FFTSolver::FFTSolver(const SignalSampling& _sampling, const bool _isInverse) : isInverse(_isInverse), sampling(_sampling) {
    try {
        if (!isPower2(sampling.sampleNo)) { // reduce data to (nearest power of 2) samples
            size_t oldSampleNo = sampling.sampleNo;
            sampling.sampleNo = nearestPower2(sampling.sampleNo);
            sampling.sampleData.resize(_sampling.sampleNo);
            sampling.length = ldouble(_sampling.sampleNo) / ldouble(_sampling.sampleRate);
            throw NonPower2Exception(oldSampleNo, sampling.sampleNo);
        }
    } catch (NonPower2Exception& exception) { exception.message(); }
}

/// Compute Fast Fourier Transform (FFT) of signal sampling
/// @param N - number of samples (reduced to a power of 2 by the class constructor if necessary)
/// @param W - complex number describing rotation of angle (1/N) on complex unit circle
/// @return Sets class field "transform" to a vector of complex numbers representing FFT of "sampling" field
void FFTSolver::FFT() {
    const auto& N = sampling.sampleNo;
    const auto W = std::exp((complex<ldouble>(2.0 * M_PI / ldouble(N)) * complex<ldouble>{0,1}));
    auto data = vecToComplex(sampling.sampleData);
    auto nArr = vector<size_t>(N);
    std::iota(nArr.begin(), nArr.end(), 0);

    transform = data;
}
