# Audio equalizer
## Overview
This project implements an equalizer of audio signal on the human-perceivable spectrum of 20-20000 Hz with the use of [Fast Fourier Transform (FFT)](https://en.wikipedia.org/wiki/Fast_Fourier_transform), with the algorithm written in C++ and signal parsing/plotting written in Python.
## Requirements
This project uses C++20 and Python 3, and as such will require:
* gcc compiler parsing "-std=c++2a" parameter (C++20 standard).
* python3 compiler
* bash shell (default location: "/bin/bash")
## Usage
Just run bash script inside the project directory, with `audiofile` being the name of a `.wav` file in the `sounds` directory:

    ./runAnalysis.sh audiofile


