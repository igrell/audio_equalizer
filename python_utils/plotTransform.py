import sys
import numpy as np
from numpy.fft import fft
from scipy.io import wavfile
import matplotlib.pyplot as plt

if __name__ == '__main__':
    inFile = open('../results/transform_output.txt')
    transformData = list(map(float, inFile.read().split()))
    sampleInterval = float(transformData[0])
    transformData = transformData[1:]
    nyquistFreq = 1 / (2 * sampleInterval)
    t = np.arange(20, 20000, 19980 / len(transformData))
    plt.plot(t, transformData, color='purple')
    plt.xlabel('Frequency (Hz)')
    plt.savefig('../results/transform_plot.png')
    # plt.show()