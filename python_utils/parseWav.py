import sys
import numpy as np
from numpy.fft import fft
from scipy.io import wavfile
import matplotlib.pyplot as plt

if __name__ == '__main__':
    audioFilename = '../sounds/' + sys.argv[1] + '.wav'
    sampleRate, audioData = wavfile.read(audioFilename)
    print('--------Loaded audio data---------')
    print('Filename:', sys.argv[1] + '.wav')
    print('Sampling Rate:', sampleRate)
    if (len(np.shape(audioData)) == 1):
        audioType = 'mono'
    else:
        audioType = 'stereo'
    print('Audio type:', audioType)
    print('----------------------------------')

    # number of samples
    sampleNo = audioData.shape[0]
    # audio time duration
    audioLen = sampleNo / sampleRate

    if len(audioData.shape) == 1:  # if mono
        outFilename = "../datafiles/data.txt"
        outFile = open(outFilename, "w")
        outFile.write(str(sampleRate))
        outFile.write('\n')
        for i in range(0, sampleNo - 1):
            outFile.write(str(audioData[i]))
            outFile.write('\n')
        outFile.write(str(audioData[sampleNo - 1]))
        outFile.close()

        # sampleInterval = 1.0 / sampleRate
        # t = np.arange(0, 1, sampleInterval)
        # plt.plot(t, audioData[0:(sampleRate)], color='purple')
        # plt.xlabel('Time (s)')
        # plt.show()


        # audio_transform = fft(audioData)
        # N = len(audio_transform)
        # n = np.arange(N)
        # T = N / sampleRate
        # freq = n / T

        # plt.plot(freq, np.abs(audio_transform), color='blue')
        # plt.xlim(0, 10)
        # plt.show()
    elif len(audioData.shape) == 2:  # if stereo
        outFilenameR = "../datafiles/dataR.txt"
        outFilenameL = "../datafiles/dataL.txt"
        outFileL, outFileR = open(outFilenameL, "w"), open(outFilenameR, "w")
        strSampleRate = str(sampleRate)
        outFileL.write(strSampleRate)
        outFileL.write('\n')
        outFileR.write(strSampleRate)
        outFileR.write('\n')
        for i in range(0, sampleNo - 1):
            outFileL.write(str(audioData[i, 0]))
            outFileL.write('\n')
            outFileR.write(str(audioData[i, 1]))
            outFileR.write('\n')
        outFileL.write(str(audioData[sampleNo - 1, 0]))
        outFileR.write(str(audioData[sampleNo - 1, 1]))

        #number of samples
        # na = audioData.shape[0]
        #audio time duration
        # la = na / sampleRate

        #plot signal versus time
        # t = np.linspace(0,la,na)
        # plt.subplot(2,1,1)
        # plt.plot(t,audioData[:,0],'b-')
        # plt.ylabel('Left')
        # plt.subplot(2,1,2)
        # plt.plot(t,audioData[:,1],'r-')
        # plt.ylabel('Right')
        # plt.xlabel('Time (s)')
        # plt.show()
    else:
        print("Wrong datafiles format")
