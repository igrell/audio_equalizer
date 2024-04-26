import sys
import numpy as np
from scipy.io import wavfile


class AudioParser:
    def __init__(self, _audioFilename):
        self.audioFilename = '../sounds/' + _audioFilename + '.wav'
        self.samplingRate, self.audioData = wavfile.read(self.audioFilename)
        self.samplingNo = self.audioData.shape[0]
        self.audioLen = self.samplingNo / self.samplingRate
        print('--------Loaded audio data---------')
        print('Filename:', _audioFilename + '.wav')
        print('Sampling Rate:', self.samplingRate)
        if len(np.shape(self.audioData)) == 1:
            self.audioType = 'mono'
        else:
            self.audioType = 'stereo'
        print('Audio type:', self.audioType)
        print('----------------------------------')

    def parseAudioToSampling(self):
        if len(self.audioData.shape) == 1:  # if mono
            outFilename = "../datafiles/data.txt"
            outFile = open(outFilename, "w")
            outFile.write(str(self.samplingRate))
            outFile.write('\n')
            for i in range(0, self.samplingNo - 1):
                outFile.write(str(self.audioData[i]))
                outFile.write('\n')
            outFile.write(str(self.audioData[self.samplingNo - 1]))
            outFile.close()
        else:
            print("Wrong audio file format")
        # if len(self.audioData.shape) == 2:  # if stereo
        #     outFilenameR = "../datafiles/dataR.txt"
        #     outFilenameL = "../datafiles/dataL.txt"
        #     outFileL, outFileR = open(outFilenameL, "w"), open(outFilenameR, "w")
        #     strSampleRate = str(self.samplingRate)
        #     outFileL.write(strSampleRate)
        #     outFileL.write('\n')
        #     outFileR.write(strSampleRate)
        #     outFileR.write('\n')
        #     for i in range(0, self.samplingNo - 1):
        #         outFileL.write(str(self.audioData[i, 0]))
        #         outFileL.write('\n')
        #         outFileR.write(str(self.audioData[i, 1]))
        #         outFileR.write('\n')
        #     outFileL.write(str(self.audioData[self.samplingNo - 1, 0]))
        #     outFileR.write(str(self.audioData[self.samplingNo - 1, 1]))


if __name__ == '__main__':
    parser = AudioParser(sys.argv[1])
    parser.parseAudioToSampling()
