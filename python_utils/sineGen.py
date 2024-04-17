import sys

import numpy as np
from scipy.io import wavfile
import sys

if __name__ == '__main__':
    noArg = len(sys.argv)
    if noArg == 1:
        sampleRate = 44100
        length = 5
        frequencies = [440]
    elif noArg == 2:
        sampleRate = int(sys.argv[1])
        length = 5
        frequencies = [440]
    elif noArg == 3:
        sampleRate = int(sys.argv[1])
        length = int(sys.argv[2])
        frequencies = [440]
    else:
        sampleRate = int(sys.argv[1])
        length = int(sys.argv[2])
        frequencies = []
        for i in range(3, noArg):
            frequencies.append(float(sys.argv[i]))

    t = np.linspace(0, length, sampleRate * length)
    waves = []
    for frequency in frequencies:
        waves.append(np.sin(frequency * 2 * np.pi * t))
    if len(waves) > 1:
        waves.append(np.sum(waves, axis=0))

    maxint16 = np.iinfo(np.int16).max

    for i in range(0, len(waves)):
        m = np.max(np.abs(waves[i]))
        waves[i] = maxint16 * waves[i] / m
        waves[i] = waves[i].astype(np.int16)
        filename = "../sounds/sine" + str(i) + ".wav"
        wavfile.write(filename, sampleRate, waves[i])
