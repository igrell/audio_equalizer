#ifndef AUDIO_EQUALIZER_FFTSOLVER_H
#define AUDIO_EQUALIZER_FFTSOLVER_H

#include "vector"
#include "complex"
#include "SignalSampling.h"
#include "cassert"

using std::vector, std::complex;
typedef unsigned long long ullong;


size_t nearestPower2(size_t N);

bool isPower2(const size_t& N);

class FFTSolver {
   SignalSampling sampling;
   bool isInverse;

public:

   FFTSolver(SignalSampling _sampling, bool _isInverse);


//   }

//   void FFT();
};



#endif //AUDIO_EQUALIZER_FFTSOLVER_H
