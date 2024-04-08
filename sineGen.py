import numpy as np
from scipy.io import wavfile

sampleRate = 44100
length = 5  # in seconds

frequencies = [440, 300, 100]

t = np.linspace(0, length, sampleRate * length)
waves = []
for frequency in frequencies:
    waves.append(np.sin(frequency * 2 * np.pi * t))
waves.append(np.sum(waves, axis=0))

maxint16 = np.iinfo(np.int16).max  # == 2**15-1

for i in range(0, len(waves)):
    m = np.max(np.abs(waves[i]))
    waves[i] = maxint16 * waves[i] / m
    waves[i] = waves[i].astype(np.int16)
    filename = "sounds/sine" + str(i) + ".wav"
    wavfile.write(filename, sampleRate, waves[i])
