#!/bin/bash
echo 'Parsing audio file to sampling format...'
cd python_utils || exit
python3 parseWav.py "${1}"
cd ..
g++ -std=c++2a SignalSampling.cpp FFTSolver.cpp fft.cpp
echo ''
echo 'Performing FFT...'
./a.out 'data.txt'
echo 'FFT sampling saved to results/transform_data.txt'
echo ''
echo 'Plotting results...'
cd python_utils || exit
python3 plotTransform.py
cd ..
rm a.out
echo 'Plot saved to results/transform_plot.png'
