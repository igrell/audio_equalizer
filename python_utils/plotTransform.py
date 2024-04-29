import numpy as np
import matplotlib.pyplot as plt


def parseDataFile(filename):
    file = open(filename)
    data = list(map(np.longdouble, file.read().split()))
    param = data[0]
    data = data[1:]
    return [param, data]


if __name__ == '__main__':
    tmp, fftData = parseDataFile('../results/fft_data.txt')
    samplingNo = len(fftData)

    tmp1, ifftData = parseDataFile('../results/ifft_data.txt')

    samplingRate, signalData = parseDataFile('../datafiles/data.txt')
    signalData = signalData[:samplingNo]  # cut data to the nearest power of 2
    length = samplingNo / samplingRate

    # Python FFTs
    pythonFft = np.fft.fft(signalData)
    pythonIfft = np.fft.ifft(pythonFft)

    # Frequencies for plotting
    samplingPoints = np.arange(samplingNo)
    frequencies = samplingPoints / length

    # Time for plotting
    time = np.linspace(0, length, samplingNo)
    # delim = 2000  # restrict plot to some first points for visual clarity; make -1 for all data
    delim = -1

    print(time)

    # Plots
    figure, axis = plt.subplots(5, 1)
    plt.subplots_adjust(hspace=3)

    axis[0].set_title('Input signal')
    axis[0].plot(time[:delim], signalData[:delim])
    axis[0].set_xlabel('Time [s]')
    axis[0].set_ylabel('Amplitude')

    axis[1].set_title('Own FT')
    axis[1].plot(frequencies[:delim], fftData[:delim])
    axis[1].set_xlabel('Frequency [Hz]')
    axis[1].set_ylabel('Amplitude')

    axis[2].set_title('Python FT')
    axis[2].plot(frequencies[:delim], abs(pythonFft[:delim]))
    axis[2].set_xlabel('Frequency [Hz]')
    axis[2].set_ylabel('Amplitude')

    axis[3].set_title('Own IFT')
    axis[3].plot(time[:delim], ifftData[:delim])
    axis[3].set_xlabel('Time [s]')
    axis[3].set_ylabel('Amplitude')

    axis[4].set_title('Python IFT')
    axis[4].plot(time[:delim], pythonIfft[:delim])
    axis[4].set_xlabel('Time [s]')
    axis[4].set_ylabel('Amplitude')

    plt.savefig('../results/transform_plot.png')
    plt.show()
