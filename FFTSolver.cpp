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

FFTSolver::FFTSolver(SignalSampling _sampling, const bool _isInverse) : isInverse(_isInverse) {
    data = vecToComplex(_sampling.sampleData);
//    std::copy(_sampling.sampleData.begin(), _sampling.sampleData.end(), std::back_inserter(data));
    auto sampleNo = data.size();
    param = isInverse ? _sampling.sampleRate : _sampling.sampleInterval;
    try {
        if (!isPower2(sampleNo)) { // reduce datafiles to (nearest power of 2) samples
            auto oldSampleNo = sampleNo;
            sampleNo = nearestPower2(sampleNo);
            data.resize(sampleNo);
            throw NonPower2Exception(oldSampleNo, sampleNo);
        }
    } catch (NonPower2Exception &exception) { exception.message(); }
}

FFTSolver::FFTSolver(vector<complex<ldouble>> _data, bool _isInverse, ldouble _param) : data(_data), isInverse(_isInverse), param(_param) {}

 void FFTSolver::computeRecFFT() { recFFT(data); }

 void FFTSolver::recFFT(vector<complex<ldouble>> &currTransform) {
     const size_t& N = currTransform.size();
     if (N < 2) return;
     size_t N2 = N >> 1;

     vector<complex<ldouble>> evens, odds;
     for (size_t i = 0 ; i < N2 ; ++i) {
         evens.emplace_back(currTransform[2 * i]);
         odds.emplace_back(currTransform[(2 * i) + 1]);
     }

     recFFT(evens);
     recFFT(odds);

     complex<ldouble> W = std::exp(complex<ldouble>((isInverse ? -1 : 1) * 2.0 * M_PI / ldouble(N) ) * complex<ldouble>{0,1} );
     complex<ldouble> Wn = {1, 0};
     complex<ldouble> oddFactor;
     for (size_t k = 0 ; k != N2 ; ++k) {
         oddFactor = Wn * odds[k];
         currTransform[k] = (evens[k] + oddFactor);
         currTransform[k + N2] = evens[k] - oddFactor;
         Wn *= W;
     }
//     for (auto& el : currTransform) { el *= (1 / N); }
 }

// TODO multiply by (1/N) for IFFT
void FFTSolver::FFT() {
    complex<ldouble> oddFactor, W, Wn;
    vector<complex<ldouble>> tmpTransform; // will save values of data from previous iter
    const size_t &N = data.size();
    const size_t N2 = N >> 1;
    data = bitReversePermuteVec(data);

//    for (auto transformLen = 2 ; transformLen != N ; transformLen <<= 1) {
//        tmpTransform = data;
//        W = std::exp(complex<ldouble>((isInverse ? -1 : 1) * 2.0 * M_PI / ldouble(N) ) * complex<ldouble>{0,1} );
//        Wn = {1,0}; // W constant, multiplied to obtain W^n in each iter
//        for(auto i = 0 ; i < N2 ; i += 2) {
//            oddFactor = Wn * tmpTransform[i + 1];
//            tmpTransform[i] = tmpTransform[i] + oddFactor;
//            tmpTransform[i + N2] = tmpTransform[i] - oddFactor;
//            Wn *= W;
//        }
//    }


    for (auto transformSize = N ; transformSize != 1 ; transformSize >>= 1) {
        tmpTransform = data;
        W = std::exp(complex<ldouble>((isInverse ? -1 : 1) * 2.0 * M_PI / ldouble(N) ) * complex<ldouble>{0,1} );
        Wn = {1,0}; // W constant, multiplied to obtain W^n in each iter
        for (auto i = 0, k = 0 ; i < N ; i += 2, ++k) { // use pair of adjacent points to get the data
            oddFactor = Wn * tmpTransform[i + 1];
            data[k] = tmpTransform[i] + oddFactor;
            data[k + N2] = tmpTransform[i] - oddFactor; // generate second half of datafiles (Danielson-Lanczos symmetry formulas)
            Wn *= W;
        }
    }
}

void saveToFile(const FFTSolver &solver) {
    ofstream file;
    string outputFilename = "results/transform_data.txt";
    if(!file.is_open()) file.open(outputFilename, std::ios::out);
    file << solver.param << "\n";
    file << solver;
    file.close();
}

vector<complex<ldouble>> FFTSolver::getData() const { return data; }


