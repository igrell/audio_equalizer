![image](./eqExample.png)
# Audio equalizer
## Overview
This project implements an equalizer of audio signal on the human-perceivable spectrum of 20-20000 Hz with the use of [Fast Fourier Transform (FFT)](https://en.wikipedia.org/wiki/Fast_Fourier_transform), with the algorithm written in C++ and signal parsing/plotting written in Python.
## Requirements
This project uses C++17 and Python 3, and as such will require:
* python3 compiler
* Python libraries: tkinter, numpy, webbrowser, scipy, contextlib, pygame
* bash shell (default location: "/bin/bash")

The C++ files come already compiled to an executable `equalize` file. However, if case of need, you can compile it yourself by invoking:

g++ -std=c++17 SignalSampling.cpp FFTSolver.cpp equalize.cpp -o equalize

## Usage
Navigate to `python_utils` and execute:

```python equalizerGUI.py```

## Note
This project was written as a part of a thesis for Bachelor's Degree in Computational Mathematics at Jagiellonian University in Kraków.

## Acknowledgements
* Icon for the equalizer app was downloaded from: https://icons8.com/icons/set/equalizer
