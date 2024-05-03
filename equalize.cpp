#ifndef EQUALIZE
#define EQUALIZE

#include <iostream>
#include "fstream"
#include "vector"
#include "SignalSampling.h"
#include "FFTSolver.h"

using std::ifstream, std::cout, std::string, std::vector, std::getline, std::stoi, std::pair;
typedef long double ldouble;
typedef pair<ldouble, ldouble> freqRange;

SignalSampling parseAudiofile(const string& filename) {
    ifstream file;
    file.open(filename, ifstream::in);

    string tmp;
    getline(file, tmp);
    size_t sampleRate = stoi(tmp);
    vector<ldouble> audioData;
    while(getline(file, tmp)) audioData.emplace_back(stoi(tmp));
    file.close();
    return {sampleRate, audioData};
}

vector<pair<freqRange, ldouble>> parseSlidersState(const string& filename) {
    ifstream file;
    file.open(filename, ifstream::in);

    vector<pair<freqRange , ldouble>> state;
    string line;
    string word;
    vector<ldouble> tmp;
    while(getline(file, line)) {
        std::istringstream ss(line);
        while (getline(ss, word, ' '))  tmp.emplace_back(stoi(word));
        state.emplace_back(freqRange(tmp[0], tmp[1]), tmp[2]);
        tmp.clear();
    }
    file.close();
    return state;
}


void equalize(const vector<pair<freqRange, ldouble>>& state, FFTSolver& solver) {
    auto dataIt = solver.getData().begin();
    auto domainIt = solver.getSolverDomain().begin();
    auto stateIt = state.begin();
    while (domainIt != solver.getSolverDomain().end() and stateIt != state.end()) {
        if (stateIt->first.first <= *domainIt and *domainIt <= stateIt->first.second) {
           // equalize this range by stateIt.second
           domainIt++;
           dataIt++;
        } else { stateIt++; }
    }
}


int main() {
    string inputFilename = "../datafiles/data.txt";
    SignalSampling audio = parseAudiofile(inputFilename);
    FFTSolver solver(audio, false);
    solver.recFFT();

    auto state = parseSlidersState("../datafiles/freqState.txt");
    equalize(state, solver);

//    saveToFile(solver);
    return 0;
}

#endif //EQUALIZE