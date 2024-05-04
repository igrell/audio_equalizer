#include "SignalSampling.h"
#include "iostream"

using std::cout, std::ostream;

ostream& operator<<(ostream& ostream, const SignalSampling& audio) {
    ostream << "-------Signal sampling data-------\n";
    ostream << "Sample rate [Hz]: " << audio.sampleRate;
    ostream << "\nNo. of samples: " << audio.sampleNo;
    ostream << "\nIn-between-samples interval: " << audio.sampleInterval;
    ostream << "\nSampling total time [s]: " << audio.length << "\n";
    ostream << "----------------------------------\n";
    return ostream;
}

SignalSampling::SignalSampling(const size_t _sampleRate, vector<ldouble> _sampleData) :
        sampleData(std::move(_sampleData)),
        sampleNo(sampleData.size()),
        sampleRate(_sampleRate),
        length(ldouble(sampleNo) / ldouble(sampleRate)),
        sampleInterval(length / ldouble(sampleNo)) {
    assert(_sampleRate != 0);
    assert(!this->sampleData.empty());
    cout << *this;
}
