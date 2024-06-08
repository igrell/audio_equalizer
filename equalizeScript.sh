#!/bin/bash
if [ ! -f equalize ]; then
    g++ -std=c++17 SignalSampling.cpp FFTSolver.cpp equalize.cpp -o equalize
fi
./equalize
