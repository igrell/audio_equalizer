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
    vector<complex<ldouble>> data;
//    vector<complex<ldouble>> transform;

public:

   FFTSolver(SignalSampling _sampling, bool _isInverse);

   vector<complex<ldouble>>FFT();
};



#endif //AUDIO_EQUALIZER_FFTSOLVER_H
