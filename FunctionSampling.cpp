#include "FunctionSampling.h"

std::ostream& operator<<(std::ostream& ostream, const FunctionSampling& audio) {
    ostream << "Sample rate [Hz]: " << audio.sampleRate;
    ostream << "\nNo. of samples: " << audio.sampleNo;
    ostream << "\nBetween-samples interval: " << audio.sampleInterval;
    ostream << "\nSampling total time [s]: " << audio.length;
    return ostream;
}
