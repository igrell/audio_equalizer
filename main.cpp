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
//        vector<long long> data{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
//        size_t rate = 5;
//        SignalSampling sampling(rate, data);
        cout << audio;
        FFTSolver solver(audio, false);
        return 0;
}

#endif //MAIN