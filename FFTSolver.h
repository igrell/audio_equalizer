#ifndef AUDIO_EQUALIZER_FFTSOLVER_H
#define AUDIO_EQUALIZER_FFTSOLVER_H

#include "vector"
#include "complex"
#include "SignalSampling.h"
#include "cassert"

using std::vector, std::complex;
typedef long double ldouble;

size_t nearestPower2(size_t N);

bool isPower2(const size_t& N);

class FFTSolver {
    SignalSampling sampling;
    const bool isInverse;
    vector<complex<ldouble>> transform;

public:

   FFTSolver(SignalSampling  _sampling, bool _isInverse);

   void computeRecFFT();

   static void recFFT(vector<complex<ldouble>>&, const size_t&);

   void FFT();
};

template<typename T>
vector<complex<T>> vecToComplex(const vector<T>& vec) {
    vector<complex<T>> res(vec.size());
    std::transform( vec.begin(), vec.end(), res.begin(),[](auto x){ return (complex<T>)x; });
    return res;
}

complex<ldouble> Wn(size_t&, size_t&);

#endif //AUDIO_EQUALIZER_FFTSOLVER_H
