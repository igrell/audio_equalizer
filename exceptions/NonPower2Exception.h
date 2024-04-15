#ifndef AUDIO_EQUALIZER_NONPOWER2EXCEPTION_H
#define AUDIO_EQUALIZER_NONPOWER2EXCEPTION_H

#include "iostream"

using std::cout;

class NonPower2Exception : public std::exception {
    size_t sampleNo = 0;
    size_t newSampleNo = 0;
public:
    NonPower2Exception() = default;

    NonPower2Exception(const size_t& _sampleNo, const size_t& _newSampleNo) : sampleNo(_sampleNo), newSampleNo(_newSampleNo) {}

    void message() const {
       cout << "\nWarning: number of samples (" << sampleNo << ") isn't a power of 2; reducing samples to a power of 2 (" << newSampleNo << ")\n";
    }
};

#endif //AUDIO_EQUALIZER_NONPOWER2EXCEPTION_H
