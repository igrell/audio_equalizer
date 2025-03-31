# ![image](./eqExample.png)
# Audio equalizer
## Overview
This project implements an equalizer of audio signal on the human-perceivable spectrum of 20-20000 Hz with the use of [Fast Fourier Transform (FFT)](https://en.wikipedia.org/wiki/Fast_Fourier_transform), with the algorithm written in C++ and signal parsing and GUI written in Python.
## Requirements
This project uses C++17 and Python 3, and as such will require:
* python3 interpreter
* Python libraries: tkinter, numpy, webbrowser, scipy, contextlib, pygame
* bash shell (default location: `/bin/bash`)

The C++ files come already compiled to an executable `equalize` file. However, if case of need, you can compile it yourself by invoking:

```g++ -std=c++17 SignalSampling.cpp FFTSolver.cpp equalize.cpp -o equalize```

## Usage
Navigate to `python_utils` and execute:

```python equalizerGUI.py```

## Note regarding the Bachelor's Thesis
This project was written as a part of a Bachelor's Degree Thesis in Computer Mathematics at Jagiellonian University in Kraków. The thesis regards Fast Fourier Transform and its applications to signal processing and data compression, from both the theorethical and practical point of view.

Read the full thesis [here](https://ujchmura-my.sharepoint.com/:b:/g/personal/igor_piechowiak_student_uj_edu_pl/Ebm17vK5qcBLovdawDtlXAkB7tdl-MCmtZhOQ3QFDhefOQ?e=vgLciI) (in Polish).

## Acknowledgements
* Icon for the equalizer app was downloaded from: https://icons8.com/icons/set/equalizer
