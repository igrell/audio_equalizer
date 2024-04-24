import numpy as np
import matplotlib.pyplot as plt


def parseDataFile(filename):
    file = open(filename)
    data = list(map(np.longdouble, file.read().split()))
    param = data[0]
    data = data[1:]
    return [param, data]


if __name__ == '__main__':
    samplingInterval, fftData = parseDataFile('../results/fft_data.txt')
    samplingNo = len(fftData)

    tmp, ifftData = parseDataFile('../results/ifft_data.txt')

    samplingRate, signalData = parseDataFile('../datafiles/data.txt')
    signalData = signalData[:samplingNo]  # cut data to the nearest power of 2
    length = samplingNo / samplingRate

    time = np.linspace(0, length, samplingNo)
    # time = np.arange(0, length, samplingInterval)
    # print(time)

    pythonFft = np.fft.fft(signalData)
    samplePoints = np.arange(samplingNo)
    frequencies = samplePoints / length

    pythonIfft = np.fft.ifft(pythonFft)


    figure, axis = plt.subplots(5, 1)
    plt.subplots_adjust(hspace=3)

    axis[0].set_title('Input signal')
    axis[0].plot(time, signalData)
    axis[0].set_xlabel('Time [s]')
    axis[0].set_ylabel('Amplitude')

    axis[1].set_title('Own FT')
    axis[1].plot(frequencies, fftData)
    axis[1].set_xlabel('Frequency [Hz]')
    axis[1].set_ylabel('Amplitude')

    axis[2].set_title('Python FT')
    axis[2].plot(frequencies, abs(pythonFft))
    axis[2].set_xlabel('Frequency [Hz]')
    axis[2].set_ylabel('Amplitude')

    axis[3].set_title('Own IFT')
    axis[3].plot(time, ifftData)
    axis[3].set_xlabel('Time [s]')
    axis[3].set_ylabel('Amplitude')

    axis[4].set_title('Python IFT')
    axis[4].plot(time, pythonIfft)
    axis[4].set_xlabel('Time [s]')
    axis[4].set_ylabel('Amplitude')

    plt.savefig('../results/transform_plot.png')
    plt.show()

    # for i in range(0, 2000):
    #     print(abs(python_fft[i])
