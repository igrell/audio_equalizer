#include "FFTSolver.h"
#include "complex"
#include "vector"
#include "iostream"
#include "NonPower2Exception.h"

using std::cout;

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
            vector<long long> newSampleData;
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

void FFTSolver::FFT() {

}
