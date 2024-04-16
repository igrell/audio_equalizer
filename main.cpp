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
    SignalSampling test(2, vector<ldouble>{0,1,2,3});
    for (auto el : test.sampleData) cout << el << " ";
    cout << "\n";
    FFTSolver testSolver(test, false);
    testSolver.computeRecFFT();
//    FFTSolver solver(audio, false);
//    solver.computeRecFFT();
    return 0;
}

#endif //MAIN