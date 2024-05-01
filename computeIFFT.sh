#!/bin/bash
cd ..
g++ -std=c++2a SignalSampling.cpp FFTSolver.cpp ifft.cpp
./a.out 'data.txt'
cd python_utils || exit
python3 plotTransform.py
cd ..
rm a.out
cd python_utils || exit
