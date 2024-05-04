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

void equalizeSample(const ldouble db, complex<ldouble>& sample) {
    auto scalar = pow(10, db / 20);
    sample *= scalar; // TODO math goes here
}

void equalize(const vector<pair<freqRange, ldouble>>& state, FFTSolver& solver) {
    auto dataIt = solver.getData().begin();
    auto domainIt = solver.getSolverDomain().begin();
    auto stateIt = state.begin();
    const ldouble* freqFrom; // TODO can be removed later
    const ldouble* freqTo;
    const ldouble* db;
    while (domainIt != solver.getSolverDomain().end() and stateIt != state.end()) {
        freqFrom = &stateIt->first.first;
        freqTo = &stateIt->first.second;
        db = &stateIt->second;
        if (*freqFrom <= *domainIt and *domainIt <= *freqTo) {
           equalizeSample(*db, *dataIt);
           domainIt++; dataIt++;
        } else {
            if (*domainIt < *freqFrom) { domainIt++; dataIt++; }
            else stateIt++;
        }
    }
}


int main() {
    string inputFilename = "datafiles/data.txt";
    SignalSampling audio = parseAudiofile(inputFilename);
    FFTSolver solver(audio, false);
    solver.recFFT();
    saveToFile(solver);

    auto state = parseSlidersState("datafiles/freqState.txt");
    equalize(state, solver);

    FFTSolver isolver(solver.getData(), true, audio.sampleRate);
    isolver.recFFT();
    saveToFile(isolver);

//    auto state = vector<pair<freqRange, ldouble>>{{{0, 1}, 2}, {{1, 2}, 3}, {{2, 3}, 4}};
//    auto data = vector<complex<ldouble>>{1, 1, 1, 1};
//    auto solver1 = FFTSolver(data, false, 4);
//    solver1.recFFT();
//    saveToFile(solver1);
//    for (auto el : solver1.getData()) cout << el << " ";
//    cout << "\n";
//    equalize(state, solver1);
//    for (auto el : solver1.getData()) cout << el << " ";
    return 0;
}

#endif //EQUALIZE