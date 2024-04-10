#ifndef AUDIO_EQUALIZER_FFTSOLVER_H
#define AUDIO_EQUALIZER_FFTSOLVER_H

#include "vector"
#include "complex"
#include "FunctionSampling.h"
#include "cassert"

using std::vector, std::complex;
typedef unsigned long long ullong;


size_t nearestPower2(size_t N);

class FFTSolver {
   FunctionSampling sampling;
   bool isInverse;

public:

   FFTSolver(FunctionSampling& _sampling, const bool _isInverse) : isInverse(_isInverse) {
        assert(sampling.sampleNo != 0);
        if ((sampling.sampleNo & (sampling.sampleNo - 1)) != 0) { // if sampleNo is not a power of 2
            size_t restSampleNo = nearestPower2(sampling.sampleNo);
            size_t restSampleRate = 1 / restSampleNo;
            vector<long long> restSampleData;
            std::copy(sampling.sampleData.begin(), sampling.sampleData.begin() + restSampleNo, std::back_inserter(restSampleData));
//            sampling = FunctionSampling(restSampleRate, restSampleData);
        }


   }

   void FFT();
};



#endif //AUDIO_EQUALIZER_FFTSOLVER_H
