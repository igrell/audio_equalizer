import numpy as np
import matplotlib.pyplot as plt
from parseWav import parseDataFile



if __name__ == '__main__':
    _, frequencies, fftData = parseDataFile('../results/fft_data.txt')
    samplingNo = len(fftData)

    _, time, ifftData = parseDataFile('../results/ifft_data.txt')

    signalData = parseDataFile('../datafiles/data.txt')
    signalData = signalData[:samplingNo]  # cut data to the nearest power of 2

    # Python FFTs
    pythonFft = np.fft.fft(signalData)
    # pythonFft = np.real(pythonFft)
    pythonIfft = np.fft.ifft(pythonFft)

    delim = 200000  # restrict plot to some first points for visual clarity; make -1 for all data
    # delim = -1

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
    axis[2].plot(frequencies[:delim], np.real(pythonFft[:delim]))
    axis[2].set_xlabel('Frequency [Hz]')
    axis[2].set_ylabel('Amplitude')

    axis[3].set_title('Own IFT')
    axis[3].plot(time[:delim], ifftData[:delim])
    axis[3].set_xlabel('Time [s]')
    axis[3].set_ylabel('Amplitude')

    axis[4].set_title('Python IFT')
    axis[4].plot(time[:delim], np.real(pythonIfft[:delim]))
    axis[4].set_xlabel('Time [s]')
    axis[4].set_ylabel('Amplitude')

    plt.savefig('../results/transform_plot.png')
    plt.show()
    print('Data: ', signalData[:5])
    print('Python FFT: ', np.real(pythonFft[:5]))
    print('Own FFT: ', fftData[:5])
    print('Python IFFT: ', np.real(pythonIfft[:5]))
    print('Own IFFT: ', np.real(ifftData[:5]))

    # input = [1, 2, 1, 2]
    # print(np.fft.fft(input))
