import numpy as np
from numpy.fft import fft
import matplotlib.pyplot as plt
import math

if __name__ == '__main__':
    transformInFile = open('../results/transform_data.txt')
    transformData = list(map(float, transformInFile.read().split()))
    sampleInterval = float(transformData[0])
    transformData = transformData[1:]
    nyquistFreq = 1 / (2 * sampleInterval)
    f = np.linspace(20, 20000, len(transformData)) # TODO fix the range of f

    signalInFile = open('../datafiles/data.txt')
    signalData = list(map(float, signalInFile.read().split()))
    signalSampleRate = signalData[0]
    signalData = signalData[1:(len(f) + 1)]
    signalSampleNo = len(signalData)
    length = signalSampleNo / signalSampleRate
    t = np.arange(0, length, sampleInterval)
    freq = 440
    noOfPeriods = 5
    t_delim = noOfPeriods * math.floor(signalSampleNo / (freq * length))
    # t_delim = len(t) - 1

    fftData = fft(signalData) / signalSampleNo
    values = np.arange(int(signalSampleNo / 2))
    timePeriod = signalSampleNo / signalSampleRate
    fft_f = values / timePeriod

    plt.subplot(3, 1, 1)
    plt.plot(t[:t_delim], signalData[:t_delim], color='blue')
    plt.xlabel('Time [s]')
    plt.ylabel('Signal value')

    plt.subplot(3, 1, 2)
    plt.plot(f, transformData, color='purple')
    plt.xlabel('Frequency [Hz]')
    plt.ylabel('Own FT value')
    plt.tight_layout()

    plt.subplot(3, 1, 3)
    plt.plot(fft_f, abs(fftData), color='red')
    plt.xlabel('Frequency [Hz]')
    plt.ylabel('Python FT value')
    plt.tight_layout()
    plt.savefig('../results/transform_plot.png')
    # plt.show()