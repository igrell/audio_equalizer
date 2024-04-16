#ifndef MAIN
#define MAIN

#include <iostream>
#include "fstream"
#include "vector"
#include "SignalSampling.h"
#include "FFTSolver.h"
#include "NonPower2Exception.h"
#include "format"

using std::ifstream, std::cout, std::string, std::vector;
typedef long double ldouble;

SignalSampling parseAudiofile(const string& filename) {
    ifstream file;
    file.open(filename, ifstream::in);

    string tmp;
    std::getline(file, tmp);
    size_t sampleRate = stoi(tmp);
    vector<ldouble> audioData;
    while(std::getline(file, tmp)) audioData.emplace_back(stoi(tmp));
    file.close();
    return {sampleRate, audioData};
}

int main() {
    SignalSampling audio = parseAudiofile("../data.txt");
    FFTSolver solver(audio, false);
    solver.FFT();
    vector<size_t> vec{0,1,2,3,4,5,6,7};
//    for (auto el : audio.sampleData) { cout << el << " "; }
    return 0;
}

#endif //MAIN