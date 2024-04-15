#ifndef AUDIO_EQUALIZER_SIGNALSAMPLING_H
#define AUDIO_EQUALIZER_SIGNALSAMPLING_H

#include "vector"
#include "sstream"
#include "cassert"

using std::vector, std::ostream;
typedef long double ldouble;

class SignalSampling {
public:
    vector<ldouble> sampleData;
    size_t sampleNo;
    size_t sampleRate;
    ldouble length;
    ldouble sampleInterval;

    SignalSampling(const size_t _sampleRate, vector<ldouble> _sampleData) :
            sampleData(std::move(_sampleData)),
            sampleNo(sampleData.size()),
            sampleRate(_sampleRate),
            length(ldouble(sampleNo) / ldouble(sampleRate)),
            sampleInterval(length / ldouble(sampleNo)) {
        assert(_sampleRate != 0);
        assert(!this->sampleData.empty());
    }
};

ostream& operator<<(ostream&, const SignalSampling&);


#endif //AUDIO_EQUALIZER_SIGNALSAMPLING_H
