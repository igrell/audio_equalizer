#ifndef MAIN
#define MAIN

#include <iostream>
#include "fstream"
#include "vector"
#include "SignalSampling.h"
#include "FFTSolver.h"
#include "NonPower2Exception.h"

using std::ifstream, std::cout, std::string, std::vector;
typedef long double ldouble;

SignalSampling parseAudiofile(const string& filename) {
    ifstream file;
    file.open(filename, ifstream::in);

    size_t sampleRate;

    string tmp;
    std::getline(file, tmp);
    sampleRate = stoi(tmp);
    vector<ldouble> audioData;
    while(std::getline(file, tmp)) audioData.emplace_back(stoi(tmp));
    file.close();
    return {sampleRate, audioData};
}

template<typename T>
vector<complex<T>> vecToComplex(const vector<T>& vec) {
    vector<complex<T>> res(vec.size());
    std::transform( vec.begin(), vec.end(), res.begin(),[](auto x){ return (complex<T>)x; });
    return res;
}

int main() {
    SignalSampling audio = parseAudiofile("../data.txt");
        cout << audio;
//        FFTSolver solver(audio, false);
        vector<double> a{1,2,3};
        vector<complex<double>> b = vecToComplex(a);
        for (auto el : b) { cout << el << "\n"; }
        return 0;
}

#endif //MAIN