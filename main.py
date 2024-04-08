import numpy as np
from scipy.io import wavfile
import matplotlib.pyplot as plt

filename = 'sounds/Drone1.wav'
sampleRate, audioData = wavfile.read(filename)
print('Sampling Rate:', sampleRate)
print('Audio Shape:', np.shape(audioData))

# number of samples
sampleNo = audioData.shape[0]
# audio time duration
audioLen = sampleNo / sampleRate

# t = np.linspace(0, audioLen, sampleNo)
# plt.plot(t, a, color='purple')
# plt.xlabel('Time (s)')
# plt.show()

if len(audioData.shape) == 1:  # if mono
    outFile = open("data.txt", "w")
    outFile.write(str(sampleRate))
    for el in audioData:
        outFile.write(str(el))
        outFile.write('\n')
    outFile.close()
elif len(audioData.shape) == 2:  # if stereo
    outFileL, outFileR = open("dataL.txt", "w"), open("dataR.txt", "w")
    strSampleRate = str(sampleRate)
    outFileL.write(strSampleRate)
    outFileR.write(strSampleRate)
    for i in range(0, sampleRate):
        outFileL.write(str(audioData[i, 0]))
        outFileL.write('\n')
        outFileR.write(str(audioData[i, 1]))
        outFileR.write('\n')
else:
    print("Wrong data format")
