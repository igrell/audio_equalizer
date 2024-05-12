#ifndef IFFT
#define IFFT

#include "SignalSampling.h"
#include "FFTSolver.h"

int main() {
    std::string inputFilename = "datafiles/after_eq.txt";
    SignalSampling audio = parseAudiofile(inputFilename);
    FFTSolver isolver(audio, true);
    isolver.recFFT();
    saveToFile(isolver);
    return 0;
}

#endif //IFFT