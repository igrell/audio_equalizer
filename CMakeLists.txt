cmake_minimum_required(VERSION 3.27)
project(audio_equalizer)

set(CMAKE_CXX_STANDARD 20)

add_executable(audio_equalizer main.cpp FunctionSampling.h FunctionSampling.cpp
        FFTSolver.cpp
        FFTSolver.h
)
