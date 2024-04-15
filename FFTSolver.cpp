#include "FFTSolver.h"
#include "complex"
#include "vector"
#include "iostream"
#include "NonPower2Exception.h"

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

FFTSolver::FFTSolver(SignalSampling _sampling, const bool _isInverse) : isInverse(_isInverse), sampling(_sampling) {
    size_t sampleNo = _sampling.sampleNo;
    try {
        if (!isPower2(sampleNo)) {
            _sampling.sampleNo = nearestPower2(sampleNo);
            vector<ldouble> newSampleData;
            std::copy(_sampling.sampleData.begin(), // TODO optimize
                      _sampling.sampleData.begin() + _sampling.sampleNo,
                      std::back_inserter(newSampleData));
            _sampling.sampleData = std::move(newSampleData);
            _sampling.length = ldouble(_sampling.sampleNo) / ldouble(_sampling.sampleRate);
            this->sampling = _sampling;
            throw NonPower2Exception(sampleNo, _sampling.sampleNo);
        }
    } catch (NonPower2Exception& exception) { exception.message(); }
}

/// Compute Fast Fourier Transform (FFT) of signal sampling
/// @param N - number of samples (reduced to a power of 2 by the class constructor if necessary)
/// @param W - complex number describing rotation of angle (1/N) on complex unit circle
vector<complex<long double>> FFTSolver::FFT() {
    const auto& N = sampling.sampleNo;
    const auto W = std::exp((complex<long double>(2.0 * M_PI / N) * complex<long double>{0,1}));

}
