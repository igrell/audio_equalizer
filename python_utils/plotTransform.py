import numpy as np
import matplotlib.pyplot as plt
import math


def parseDataFile(filename):
    file = open(filename)
    data = list(map(np.longdouble, file.read().split()))
    param = data[0]
    data = data[1:]
    return [param, data]


if __name__ == '__main__':
    samplingInterval, transformData = parseDataFile('../results/transform_data.txt')
    samplingNo = len(transformData)

    samplingRate, signalData = parseDataFile('../datafiles/data.txt')
    signalData = signalData[:samplingNo]  # cut data to the nearest power of 2
    length = samplingNo / samplingRate

    time = np.linspace(0, length, samplingNo)
    # time = np.arange(0, length, samplingInterval)
    # print(time)

    python_fft = np.fft.fft(signalData)
    samplePoints = np.arange(samplingNo)
    frequencies = samplePoints / length

    figure, axis = plt.subplots(3, 1)
    plt.subplots_adjust(hspace=2)

    axis[0].set_title('Input signal')
    axis[0].plot(time, signalData)
    axis[0].set_xlabel('Time [s]')
    axis[0].set_ylabel('Amplitude')

    axis[1].set_title('Own FT')
    axis[1].plot(frequencies[:2000], transformData[:2000])
    axis[1].set_xlabel('Frequency [Hz]')
    axis[1].set_ylabel('Amplitude')

    axis[2].set_title('Python FT')
    axis[2].plot(frequencies[:2000], abs(python_fft)[:2000])
    axis[2].set_xlabel('Frequency [Hz]')
    axis[2].set_ylabel('Amplitude')

    plt.savefig('../results/transform_plot.png')
    plt.show()

    # for i in range(0, 2000):
    #     print(abs(python_fft[i])
