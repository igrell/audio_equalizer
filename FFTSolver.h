#ifndef AUDIO_EQUALIZER_FFTSOLVER_H
#define AUDIO_EQUALIZER_FFTSOLVER_H

#include "vector"
#include "complex"
#include "SignalSampling.h"
#include "cassert"
#include "format"
#include "iostream"
#include "fstream"

using std::vector, std::complex, std::ostream, std::cout, std::ofstream;
typedef long double ldouble;

/// @class  FFTSolver
/// @param data input of iterFFT/IFFT algorithm; filled either with signal sampling or FT points to be reversed by IFFT during class construction
/// @param domainData for FFT - time intervals, for IFFT - frequency intervals; used for plotting and EQ manipulation
/// @param isInverse indicates whether an instance of FFTSolver will be used to calculate iterFFT or IFFT
/// @param param parameter useful for plotting; samplingInterval for iterFFT, samplingRate for IFFT
class FFTSolver {
    vector<complex<ldouble>> data;
    vector<ldouble> domainData;
    const bool isInverse;
    ldouble param;

public:

   FFTSolver(const SignalSampling&, bool);

   FFTSolver(vector<complex<ldouble>>, bool, ldouble);

   void recFFT();

   void recFFTStep(vector<complex<ldouble>> &currTransform);

/// Compute Fast Fourier Transform (iterFFT) of signal sampling
/// @param N - number of samples (reduced to a power of 2 by the class constructor if necessary)
/// @param W - complex number describing rotation of angle (1/N) on complex unit circle
/// @return Sets class field "data" to a vector of complex numbers representing iterFFT of "sampling" field
   void iterFFT();


    friend ostream& operator<<(ostream& ostream, const FFTSolver& solver) {
        for(auto i = 0 ; i < solver.data.size() - 1 ; ++i) ostream <<
        solver.domainData[i] <<  " " <<
        (solver.isInverse ? solver.data[i].real() : abs(solver.data[i])) << "\n";
//        for (auto it = solver.data.begin() ; (it + 1) != solver.data.end() ; it++) ostream << (solver.isInverse ? (*it).real() : abs(*it) ) << " " << "\n";
        ostream << solver.domainData.back() <<  " " << abs(solver.data.back());
        return ostream;
    }

    friend void saveToFile(const FFTSolver&);

    vector<complex<ldouble>> getData() const;

    vector<complex<ldouble>>& getData();

    vector<ldouble> getSolverDomain() const;

    vector<ldouble>& getSolverDomain();  // TODO this is disgusting, check todo below

    void setInverse(bool);

};

size_t nearestPower2(size_t N);

bool isPower2(const size_t& N);

template<typename T>
vector<complex<T>> vecToComplex(const vector<T>& vec);

template<typename T>
inline size_t bitLen(T n);

/// Reverse bits of a number
/// @param n Number to bit-reverse
/// @param len Number of bytes according to type known from context; this is important as padding zeroes change the result
template<typename T>
T bitReverse(T n, size_t len);

/// Permute vector according to bit-reversing indexes of its elements
/// @example {0,1,2,3,4,5,6,7} ->\n {0,4,2,6,1,5,3,7} \n Because in indexes\n {000,001,010,011,100,101,110,111} ->\n {000,100,010,110,001,101,011,111}
///
template<typename T>
vector<T> bitReversePermuteVec(const vector<T>& vec);

/// Return frequency domain for FFT and time domain for IFFT
template<typename T>
vector<T> getDomain(const ldouble&, const size_t&, const bool&); // TODO move this to class body one day


#endif //AUDIO_EQUALIZER_FFTSOLVER_H
