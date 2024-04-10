#ifndef MAIN
#define MAIN

#include <iostream>
#include "fstream"
#include "vector"
#include "FunctionSampling.h"
#include "FFTSolver.h"

using std::ifstream, std::cout, std::string, std::vector;

FunctionSampling parseAudiofile(const string& filename) {
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
    FunctionSampling audio = parseAudiofile("../data.txt");
//    cout << audio;
    auto solver = FFTSolver(audio, false);
    cout << nearestPower2(129);
    return 0;
}

#endif //MAIN