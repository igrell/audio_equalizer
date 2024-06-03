#include <iostream>
#include <fstream>
#include <vector>
#include "SignalSampling.h"

using std::cout, std::ostream, std::string, std::ifstream, std::vector;

ostream& operator<<(ostream& ostream, const SignalSampling& audio) {
    ostream << "-------Signal sampling data-------\n";
    ostream << "Sample rate [Hz]: " << audio.sampleRate;
    ostream << "\nNo. of samples: " << audio.sampleNo;
    ostream << "\nIn-between-samples interval: " << audio.sampleInterval;
    ostream << "\nSampling total time [s]: " << audio.length << "\n";
    ostream << "----------------------------------\n";
    return ostream;
}

SignalSampling parseAudiofile(const string& filename) {
    ifstream file;
    file.open(filename, ifstream::in);

    string tmp;
    getline(file, tmp);
    size_t param = stoi(tmp);
    vector<ldouble> audioData;
    while(getline(file, tmp)) audioData.emplace_back(stoi(tmp));
    file.close();
    return {param, audioData};
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
