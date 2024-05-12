#ifndef FFT
#define FFT

#include "SignalSampling.h"
#include "FFTSolver.h"

int main() {
    std::string inputFilename = "datafiles/data.txt";
    SignalSampling audio = parseAudiofile(inputFilename);
    FFTSolver solver(audio, false);
    solver.recFFT();
    saveToFile(solver);
    return 0;
}

#endif //FFT