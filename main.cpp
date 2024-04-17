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

void saveToFile(const FFTSolver& solver) {
    std::ofstream file;
    if(!file.is_open()) file.open("../fft_output.txt", std::ios::out);
    file << solver;
    file.close();

}


int main() {
    SignalSampling audio = parseAudiofile("../data.txt");
    SignalSampling test(4, vector<ldouble>{0,1,2,3,4,5});
    FFTSolver solver(audio, false);
    solver.FFT();
    cout << solver;
    saveToFile(solver);
    return 0;
}

#endif //MAIN