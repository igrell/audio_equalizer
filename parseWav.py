import sys
import numpy as np
from scipy.io import wavfile
import matplotlib.pyplot as plt

if __name__ == '__main__':
    filename = 'sounds/' + sys.argv[1] + '.wav'
    sampleRate, audioData = wavfile.read(filename)
    print('Sampling Rate:', sampleRate)
    print('Audio Shape:', np.shape(audioData))

    # number of samples
    sampleNo = audioData.shape[0]
    # audio time duration
    audioLen = sampleNo / sampleRate

    if len(audioData.shape) == 1:  # if mono
        outFile = open("data.txt", "w")
        outFile.write(str(sampleRate))
        outFile.write('\n')
        for i in range(0, sampleNo - 1):
            outFile.write(str(audioData[i]))
            outFile.write('\n')
        outFile.write(str(audioData[sampleNo - 1]))
        outFile.close()
        # t = np.linspace(0, audioLen, sampleNo)
        # plt.plot(t, a, color='purple')
        # plt.xlabel('Time (s)')
        # plt.show()
    elif len(audioData.shape) == 2:  # if stereo
        outFileL, outFileR = open("dataL.txt", "w"), open("dataR.txt", "w")
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
    else:
        print("Wrong data format")
