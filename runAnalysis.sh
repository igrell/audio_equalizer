#!/bin/bash
cd python_utils || exit
python3 parseWav.py "${1}"
cd ..
g++ -std=c++2a SignalSampling.cpp FFTSolver.cpp exceptions/NonPower2Exception.h main.cpp
./a.out 'data.txt'
cd python_utils || exit
python3 plotTransform.py
cd ..