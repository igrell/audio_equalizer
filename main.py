# import wave
import numpy as np
import matplotlib.pyplot as plt
from scipy.io import wavfile
from scipy import signal
from pydub import AudioSegment

#Import the .wav audio
f = 'sounds/sine3.wav'
s, a = wavfile.read(f)
print('Sampling Rate:', s)
print('Audio Shape:', np.shape(a))

for i in range(0, 200):
    print(a[i])

#number of samples
na = a.shape[0]
#audio time duration
la = na / s

#plot signal versus time
t = np.linspace(0, la, na)
plt.plot(t, a, color='purple')
plt.xlabel('Time (s)')
plt.show()