#ifndef AUDIO_EQUALIZER_SIGNALSAMPLING_H
#define AUDIO_EQUALIZER_SIGNALSAMPLING_H

#include "vector"
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

    SignalSampling(size_t _sampleRate, vector<ldouble> _sampleData);
};

ostream& operator<<(ostream&, const SignalSampling&);


#endif //AUDIO_EQUALIZER_SIGNALSAMPLING_H
