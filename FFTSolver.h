#ifndef AUDIO_EQUALIZER_FFTSOLVER_H
#define AUDIO_EQUALIZER_FFTSOLVER_H

#include "vector"
#include "complex"

using std::vector, std::complex;
typedef unsigned long long ullong;

class FFTSolver {
   vector<complex<long double>> data;
   ullong sampleNo;
   bool isInverse;

public:
   FFTSolver(vector<complex<long double>> &_data, const ullong &_sampleNo, const bool _isInverse) : data(std::move(_data)), sampleNo(_sampleNo), isInverse(_isInverse) {}

   void getFFT();

};



#endif //AUDIO_EQUALIZER_FFTSOLVER_H
