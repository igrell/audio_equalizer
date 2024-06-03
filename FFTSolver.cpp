#include "FFTSolver.h"

#include <utility>
#include <complex>
#include <vector>
#include <format>
#include <algorithm>
#include <numeric>
#include "exceptions/NonPower2Exception.h"

using std::vector, std::complex, std::exp, std::ofstream;
typedef long double ldouble;
typedef complex<ldouble> cld;

size_t nearestPower2up(size_t N) {
    if (N == 1) return 1;
    size_t res = 2;
    while ((N = N >> 1) != 1) res = res << 1;
    return res << 1;
}

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
    vector<T> res(N);
    size_t len = bitLen(N - 1); // get length suitable to 2^n
    for (size_t i = 0 ; i < N ; ++i) res[i] = vec[bitReverse(i, len)]; // edge indexes changed as edges never swap
    return res;
}
template vector<cld> bitReversePermuteVec(const vector<cld>&);
template vector<int> bitReversePermuteVec(const vector<int>&);

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
template int bitReverse(int, size_t);

template<typename T>
vector<complex<T>> vecToComplex(const vector<T> &vec) {
    vector<complex<T>> res(vec.size());
    std::transform( vec.begin(), vec.end(), res.begin(),[](auto x){ return (complex<T>)x; });
    return res;
}
template vector<cld> vecToComplex(const vector<ldouble>&);

FFTSolver::FFTSolver(const SignalSampling& _sampling, const bool _isInverse) : isInverse(_isInverse) {
    data = vecToComplex(_sampling.sampleData);
    audioSampleNo = data.size();
    auto sampleNo = audioSampleNo;
    param = isInverse ? ldouble(_sampling.sampleRate) : _sampling.sampleInterval;
    try {
        if (!isPower2(sampleNo)) { // reduce datafiles to (nearest power of 2) samples
            auto oldSampleNo = sampleNo;
            sampleNo = nearestPower2(sampleNo);
            data.resize(sampleNo);
            domainData = getDomain<ldouble>(ldouble(sampleNo) / ldouble(_sampling.sampleRate), sampleNo, isInverse);
            throw NonPower2Exception(oldSampleNo, sampleNo);
        }
        domainData = getDomain<ldouble>(ldouble(sampleNo) / ldouble(_sampling.sampleRate), sampleNo, isInverse);
    } catch (NonPower2Exception &exception) { exception.message(); }
}

FFTSolver::FFTSolver(vector<cld> _data, bool _isInverse, ldouble _param) : data(std::move(_data)), isInverse(_isInverse), param(_param) {
    domainData = getDomain<ldouble>(ldouble(data.size()) / _param, data.size(), isInverse); }

 void FFTSolver::recFFT() {
    if (isInverse) for (auto& el : data) { el /= data.size(); }
    recFFTStep(data);
}

 void FFTSolver::recFFTStep(vector<cld> &currTransform) {
     const size_t& N = currTransform.size();
     if (N < 2) return;
     size_t N2 = N >> 1;

     vector<cld> evens, odds;
     for (size_t i = 0 ; i < N2 ; ++i) {
         evens.emplace_back(currTransform[2 * i]);
         odds.emplace_back(currTransform[(2 * i) + 1]);
     }

     recFFTStep(evens);
     recFFTStep(odds);

     cld W;
     cld oddFactor;
     for (size_t k = 0 ; k != N2 ; ++k) {
         W = exp(cld((isInverse ? -1 : 1) * 2.0 * M_PI * ldouble(k) / ldouble(N) ) * cld{0,1} );
         oddFactor = W * odds[k];
         currTransform[k] = (evens[k] + oddFactor);
         currTransform[k + N2] = evens[k] - oddFactor;
     }
 }

 void FFTSolver::FFT() {
    data = bitReversePermuteVec(data);
    const size_t &N = data.size();
    unsigned m = 1, m2; // (m/2)
    size_t id1, id2;
    cld omega, omega_m, t, u;
    auto rotation_constant = (isInverse ? -1. : 1.) * ldouble(2. * M_PI) * cld{0, 1};
    for (size_t s = 1; s <= log2(N) ; ++s) {
       m2 = m;
       m <<= 1;
       omega_m = exp(rotation_constant / ldouble(m));
       for (size_t k = 0 ; k < N ; k += m) {
           omega = cld{1, 0};
           for (size_t j = 0 ; j < m2 ; ++j) {
              id1 = k + j;
              id2 = id1 + m2;
              t = data[id2] * omega;
              u = data[id1];
              data[id1] = u + t;
              data[id2] = u - t;
              omega *= omega_m;
           }
       }
    }
    if (isInverse) std::transform(data.begin(), data.end(), data.begin(), [&N](auto& el){ return el / ldouble(N); });
}

void saveToFile(const FFTSolver &solver) {
    ofstream file;
    std::string outputFilename = solver.isInverse ? "results/ifft_data.txt" : "results/fft_data.txt";
    if(!file.is_open()) file.open(outputFilename, std::ios::out);
    file << solver.param << "\n";
    file << solver;
    file.close();
}

vector<cld> FFTSolver::getData() const { return data; }

vector<ldouble> FFTSolver::getSolverDomain() const { return domainData; }

vector<ldouble>& FFTSolver::getSolverDomain() { return domainData; }

vector<cld>& FFTSolver::getData() { return data; }

unsigned long FFTSolver::getAudioSampleNo() const { return audioSampleNo; }

void FFTSolver::resizeData(const size_t N) { data.resize(N); }

template<typename T>
vector<T> getDomain(const ldouble& length, const size_t& samplingNo, const bool& isInverse) {
    vector<T> res(samplingNo);
    auto step = isInverse ? (length / ldouble(samplingNo)) : (1 / length) ;
    std::iota(res.begin(), res.end(), 0);
    std::for_each(res.begin(), res.end(), [&step](auto& x){ x *= step; });
    return res;
}

template vector<ldouble> getDomain(const ldouble&,const size_t&, const bool&);
