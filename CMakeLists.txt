cmake_minimum_required(VERSION 3.27)
project(audio_equalizer)

set(CMAKE_CXX_STANDARD 20)

add_executable(audio_equalizer main.cpp SignalSampling.h SignalSampling.cpp
        FFTSolver.cpp
        FFTSolver.h
        exceptions/NonPower2Exception.h
)
target_include_directories(audio_equalizer PRIVATE exceptions/)
