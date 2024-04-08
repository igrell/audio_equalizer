# import wave
import numpy as np
import matplotlib.pyplot as plt
from scipy.io import wavfile

#Import the .wav audio
f = 'sounds/Drone1.wav'
s, a = wavfile.read(f)
print('Sampling Rate:', s)
print('Audio Shape:', np.shape(a))

#number of samples
sampleNo = a.shape[0]
#audio time duration
audioLen = sampleNo / s

t = np.linspace(0, audioLen, sampleNo)
plt.plot(t, a, color='purple')
plt.xlabel('Time (s)')
plt.show()

if len(a.shape) == 1: # if mono
    outFile = open("data.txt", "w")
    outFile.write(str(s))
    for el in a:
        outFile.write(str(el))
        outFile.write('\n')
    outFile.close()
elif len(a.shape) == 2:  # if stereo
    outFileL = open("dataL.txt", "w")
    outFileR = open("dataR.txt", "w")
    outFileL.write(str(s))
    outFileR.write(str(s))
    for i in range(0, s):
        outFileL.write(str(a[i, 0]))
        outFileL.write('\n')
        outFileR.write(str(a[i, 1]))
        outFileR.write('\n')
else:
    print("Wrong data format")
