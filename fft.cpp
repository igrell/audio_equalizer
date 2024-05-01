#ifndef FFT
#define FFT

#include <iostream>
#include "fstream"
#include "vector"
#include "SignalSampling.h"
#include "FFTSolver.h"

using std::ifstream, std::cout, std::string, std::vector;
typedef long double ldouble;

SignalSampling parseAudiofile(const string& filename) {
    ifstream file;
    file.open(filename, ifstream::in);

    string tmp;
    std::getline(file, tmp);
    size_t sampleRate = std::stoi(tmp);
    vector<ldouble> audioData;
    while(std::getline(file, tmp)) audioData.emplace_back(stoi(tmp));
    file.close();
    return {sampleRate, audioData};
}


int main() {
    string inputFilename = "datafiles/data.txt";
    SignalSampling audio = parseAudiofile(inputFilename);
    FFTSolver solver(audio, false);
    solver.recFFT();
//    solver.iterFFT();
//    FFTSolver isolver(solver.getData(), true, audio.sampleRate);
//    isolver.recFFT();
    saveToFile(solver);
//    saveToFile(isolver);
    return 0;
}

#endif //FFT