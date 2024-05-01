#ifndef IFFT
#define IFFT

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
    size_t param = std::stoi(tmp);
    vector<ldouble> audioData;
    while(std::getline(file, tmp)) audioData.emplace_back(stoi(tmp));
    file.close();
    return {param, audioData};
}


int main() {
    string inputFilename = "datafiles/after_eq.txt";
    SignalSampling audio = parseAudiofile(inputFilename);
    FFTSolver isolver(audio, true);
    isolver.recFFT();
    saveToFile(isolver);
    return 0;
}

#endif //IFFT