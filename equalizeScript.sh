#!/bin/bash
g++ -std=c++2a SignalSampling.cpp FFTSolver.cpp equalize.cpp
./a.out
rm a.out
