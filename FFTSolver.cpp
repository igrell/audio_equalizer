#include "FFTSolver.h"

#include <utility>
#include "complex"
#include "vector"
#include "iostream"
#include "exceptions/NonPower2Exception.h"
#include "format"
#include "algorithm"

using std::cout, std::pair, std::transform, std::string;
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

template<typename T>
size_t bitLen(T n) { return (std::format("{:b}", n)).length(); }
template size_t bitLen(size_t);

template<typename T>
vector<T> bitReversePermuteVec(const vector<T> &vec) {
    const auto &N = vec.size();
    vector<T> res = vec;
    size_t len = bitLen(N - 1); // get length suitable to 2^n
    for (size_t i = 1 ; i < (N / 2) - 1 ; ++i) std::swap(res.at(i), res.at(bitReverse(i, len))); // edge indexes changed as edges never swap
    return res;
}
template vector<complex<ldouble>> bitReversePermuteVec(const vector<complex<ldouble>>&);

template<typename T>
T bitReverse(T n, size_t len) {
    T res = 0;
    size_t noBytes = len;
    while(noBytes--) {
        res = (res << 1) | (n & 1); // if least significant digit is 1, append to res and make room for next digit
        n >>= 1; // shift right to check next least sig. digit
    }
    return res;
}
template size_t bitReverse(size_t, size_t);

template<typename T>
vector<complex<T>> vecToComplex(const vector<T> &vec) {
    vector<complex<T>> res(vec.size());
    transform( vec.begin(), vec.end(), res.begin(),[](auto x){ return (complex<T>)x; });
    return res;
}
template vector<complex<ldouble>> vecToComplex(const vector<ldouble>&);

FFTSolver::FFTSolver(SignalSampling _sampling, const bool _isInverse) : isInverse(_isInverse),
                                                                        sampling(std::move(_sampling)),
                                                                        W(std::exp((complex<ldouble>((_isInverse ? -1 : 1) * 2.0 * M_PI / ldouble(
                                                                                nearestPower2(sampling.sampleNo))) * complex<ldouble>{0, 1}))) {
    try {
        if (!isPower2(sampling.sampleNo)) { // reduce datafiles to (nearest power of 2) samples
            auto oldSampleNo = sampling.sampleNo;
            sampling.sampleNo = nearestPower2(sampling.sampleNo);
            sampling.sampleData.resize(sampling.sampleNo);
            sampling.length = ldouble(sampling.sampleNo) / ldouble(sampling.sampleRate);
            throw NonPower2Exception(oldSampleNo, sampling.sampleNo);
        }
    } catch (NonPower2Exception &exception) { exception.message(); }
}


 void FFTSolver::computeRecFFT() {
     std::copy(sampling.sampleData.begin(), sampling.sampleData.end(), std::back_inserter(transform));
     recFFT(transform);
 }

 void FFTSolver::recFFT(vector<complex<ldouble>> &currTransform) {
     size_t N = currTransform.size();
     if (N == 1) return;
     size_t N2 = N / 2;

     vector<complex<ldouble>> evens;
     vector<complex<ldouble>> odds;
     for (size_t i = 0 ; i < N2 ; ++i) {
         evens.emplace_back(currTransform[2 * i]);
         odds.emplace_back(currTransform[2 * i + 1]);
     }
     recFFT(evens);
     recFFT(odds);

     complex<ldouble> Wn = {1, 0};
     for (size_t i = 0 ; i != N2 ; ++i) {
         currTransform[i] = evens[i] + (Wn * odds[i]);
         currTransform[i + N2] = evens[i] - (Wn * odds[i]);
        Wn *= W;
     }
 }

// TODO multiply by (1/N) for IFFT
void FFTSolver::FFT() {
    const auto &N = sampling.sampleNo;
    transform = bitReversePermuteVec(vecToComplex(sampling.sampleData));
    vector<complex<ldouble>> tmpTransform; // will save values of transform from previous iter
    auto Wn = complex<ldouble>{1,0}; // W constant, multiplied to obtain W^n in each iter
    for (auto transformSize = N ; transformSize != 1 ; transformSize >>= 1) {
        tmpTransform = transform;
        for (auto i = 0, j = 0 ; i < N ; i += 2, ++j) { // use pair of adjacent points to get the transform
            Wn *= W;
            transform.at(j) = tmpTransform.at(i) + (Wn * tmpTransform.at(i + 1));
            transform.at(j + (N >> 1)) = tmpTransform.at(i) - (Wn * tmpTransform.at(i + 1)); // generate second half of datafiles (Danielson-Lanczos symmetry formulas)
        }
    }
}

void saveToFile(const FFTSolver &solver) {
    ofstream file;
    string outputFilename = "results/transform_data.txt";
    if(!file.is_open()) file.open(outputFilename, std::ios::out);
    file << solver.sampling.sampleInterval << "\n";
    file << solver;
    file.close();
}
