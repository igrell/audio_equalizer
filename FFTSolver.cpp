#include "FFTSolver.h"

#include <utility>
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

bool isPower2(const size_t &N) {
    return (N > 0 && ((N & (N - 1)) == 0));
}

complex<ldouble> Wn(const size_t &N, const size_t &n) {
    return std::exp((complex<ldouble>(2.0 * M_PI * n / ldouble(N)) * complex<ldouble>{0, 1}));
}

FFTSolver::FFTSolver(SignalSampling _sampling, const bool _isInverse) : isInverse(_isInverse),
                                                                        sampling(std::move(_sampling)) {
    try {
        if (!isPower2(sampling.sampleNo)) { // reduce data to (nearest power of 2) samples
            auto oldSampleNo = sampling.sampleNo;
            sampling.sampleNo = nearestPower2(sampling.sampleNo);
            sampling.sampleData.resize(sampling.sampleNo);
            sampling.length = ldouble(sampling.sampleNo) / ldouble(sampling.sampleRate);
            throw NonPower2Exception(oldSampleNo, sampling.sampleNo);
        }
    } catch (NonPower2Exception &exception) { exception.message(); }
}

/// Compute Fast Fourier Transform (FFT) of signal sampling
/// @param N - number of samples (reduced to a power of 2 by the class constructor if necessary)
/// @param W - complex number describing rotation of angle (1/N) on complex unit circle
/// @return Sets class field "transform" to a vector of complex numbers representing FFT of "sampling" field
void FFTSolver::FFT() {
    const auto &N = sampling.sampleNo;
    const auto W = std::exp((complex<ldouble>(2.0 * M_PI / ldouble(N)) * complex<ldouble>{0, 1}));
    auto data = vecToComplex(sampling.sampleData);
    auto nArr = vector<size_t>(N);
    std::iota(nArr.begin(), nArr.end(), 0);

    transform = data;
}

void FFTSolver::computeRecFFT() {
    std::copy(sampling.sampleData.begin(), sampling.sampleData.end(), std::back_inserter(transform));
    recFFT(transform, transform.size());
    for (const auto &el: transform) { cout << el << " "; }
}

void FFTSolver::recFFT(vector<complex<ldouble>> &currTransform, const size_t &N) {
    if (N == 2) {
        auto tmp = currTransform[0];
        currTransform.at(0) += currTransform.at(1);
        currTransform.at(1) = tmp - currTransform.at(1);
    } else {
        vector<complex<ldouble>> evens, odds;
        for (int i = 0; i < currTransform.size(); i += 2) {
            evens.emplace_back(currTransform[i]);
            odds.emplace_back(currTransform[i + 1]);
        }
        auto N2 = N / 2;
        recFFT(evens, N2);
        recFFT(odds, N2);
        for (int n = 0; n < N2; ++n) {
            currTransform.at(n) = evens.at(n) + (Wn(N, n) * odds.at(n)); // TODO optimize Wn
        }
    }
}