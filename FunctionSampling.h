#ifndef AUDIO_EQUALIZER_FUNCTIONSAMPLING_H
#define AUDIO_EQUALIZER_FUNCTIONSAMPLING_H

#include "vector"
#include "sstream"

using std::vector, std::ostream;
typedef long double ldouble;

class FunctionSampling {
public:
    vector<long long> sampleData;
    const size_t sampleNo;
    const size_t sampleRate;
    const ldouble length;
    const ldouble sampleInterval;

    FunctionSampling(const size_t _sampleRate, vector<long long> _sampleData) :
            sampleData(std::move(_sampleData)),
            sampleNo(sampleData.size()),
            sampleRate(_sampleRate),
            length(ldouble(sampleNo) / ldouble(sampleRate)),
            sampleInterval(length / ldouble(sampleNo)) {}
};

ostream& operator<<(ostream&, const FunctionSampling&);


#endif //AUDIO_EQUALIZER_FUNCTIONSAMPLING_H
