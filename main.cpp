#ifndef MAIN
#define MAIN

#include <iostream>
#include "fstream"
#include "vector"
#include "SignalSampling.h"
#include "FFTSolver.h"
#include "NonPower2Exception.h"

using std::ifstream, std::cout, std::string, std::vector;

SignalSampling parseAudiofile(const string& filename) {
    ifstream file;
    file.open(filename, ifstream::in);

    size_t sampleRate;

    string tmp;
    std::getline(file, tmp);
    sampleRate = stoi(tmp);
    vector<long long> audioData;
    while(std::getline(file, tmp)) audioData.emplace_back(stoi(tmp));
    file.close();
    return {sampleRate, audioData};
}


int main() {
    SignalSampling audio = parseAudiofile("../data.txt");
        cout << audio;
        FFTSolver solver(audio, false);
        return 0;
}

#endif //MAIN