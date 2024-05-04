import subprocess
import tkinter as tk
from tkinter import *
from tkinter import filedialog as fd

import numpy as np
from PIL import Image, ImageTk
import webbrowser
import contextlib
from parseWav import AudioParser
from parseWav import parseDataFile
from scipy.io import wavfile

with contextlib.redirect_stdout(None):  # Hide pygame welcome prompt
    from pygame import mixer

def openURL():
    webbrowser.open('https://github.com/igrell/audio_equalizer')


def getFreqRanges():
    _freqMin, _freqMax = 20, 20000
    _freqRanges = []
    if slidersNo.get() == 10:  # ISO standard for 10 bands
        _freqRanges = [20, 40, 80, 160, 320, 640, 1280, 2560, 5120, 10240, 20000]
    elif slidersNo.get() == 31:  # ISO standard for 31 bands
        _freqRanges = [20, 25, 31.5, 40, 50, 63, 80, 100, 125, 160, 200, 250, 315, 400, 500, 630, 800, 1000, 1250, 1600,
                       2000, 2500, 3150, 4000, 5000, 6300, 8000, 10000, 12500, 16000, 20000]
    _freqRanges = list(zip(_freqRanges, _freqRanges[1:]))  # Generate pairs of frequencies
    return _freqRanges


def getLabelName(freq):
    if freq < 1000.0:
        return str(int(freq)) + ' Hz'
    else:
        return str(round(freq / 1000, 1)) + ' kHz'


def loadAudioFile(event=None):
    audiofilename.set(fd.askopenfilename())
    if audiofilename.get() != '':
        filetype = audiofilename.get().split('.')[1]
        if filetype != 'wav':
            print('Wrong filetype! Please insert a WAV file')
            return None
        else:
            print('Loaded audio file: ', audiofilename.get().split('/')[-1])
            dialoguestr.set('Audio file loaded.')
            return audiofilename


def quitApp(event=None):  # TODO this needn't be here
    window.quit()


def playAudio(event=None):  # TODO show 'play' again when audio finishes
    if audiofilename.get() == '':
        dialoguestr.set('No audio to play.')
    else:
        mixer.music.load(audiofilename.get())
        if playButton["text"] == "Play":
            playButton["text"] = "Pause"
            mixer.music.play()
            # playButton["text"] == "Play"
        else:
            playButton["text"] = "Play"
            mixer.music.pause()



def getSlidersState():
    state = []
    for i in range(0, slidersNo.get()):
        state.append([freqRanges[i][0], freqRanges[i][1], sliders[i].get()])
    return state


def sliderStateToTxt(state):
    outFilename = "../datafiles/freqState.txt"
    statetxt = ''
    for i in range(0, len(state) - 1):
        statetxt += str(state[i][0]) + ' ' + str(state[i][1]) + ' ' + str(state[i][2]) + '\n'
    statetxt += str(state[len(state) - 1][0]) + ' ' + str(state[len(state) - 1][1]) + ' ' + str(state[len(state) - 1][2])
    open(outFilename, "w").write(statetxt)

def getFilename(filepath):
    return filepath.split('/')[-1].split('.')[0]

def equalize(event=None):
    if audiofilename.get() == '':
        dialoguestr.set('No audio to equalize.')
    else:
        parser = AudioParser(getFilename(audiofilename.get()))
        parser.parseAudioToSampling()
        slidersState = getSlidersState()
        sliderStateToTxt(slidersState)
        subprocess.call("cd .. && ./equalizeScript.sh && cd python_utils", shell=True)
        samplingRate, _, ifftData = parseDataFile("../results/ifft_data.txt")  # can be later changed to data
        samplingRate = int(samplingRate)
        ifftData = ifftData.astype(np.int16)
        newAudioFilename = '../sounds/newAudio.wav'
        wavfile.write(newAudioFilename, samplingRate, ifftData.astype(np.int16))
        dialoguestr.set('Changes applied.')



def loadTestSound(event=None):
    audiofilename.set('/Users/igor/Documents/Kod/Proseminarium/audio_equalizer/sounds/airhorn.wav')
    dialoguestr.set('Audio file loaded.')


def resetSliders(event=None):
    for slider in sliders:
        slider.set(0.0)
    dialoguestr.set('Equalizer parameters reset.')


def setSliders():
    # sliders.clear()
    # for freq in freqRanges:
    #     slider = Slider(window, sliderWidth, freq)
    #     sliders.append(slider)
    sliders.clear()
    inputFields.clear()
    labels.clear()
    # Initialize sliders
    for j in range(0, slidersNo.get()):
        sliderVar = tk.DoubleVar()
        slider = Scale(window, from_=amplifyFrom, to=amplifyTo, variable=sliderVar, resolution=0.1, length=150,
                       width=sliderWidth.get(), showvalue=True)  # TODO think if i can afford showing value
        inputField = Entry(window, width=4, textvariable=sliderVar)
        slider.set((amplifyFrom + amplifyTo) / 2)
        sliders.append(slider)
        inputFields.append(inputField)

    # Frequency ranges for sliders
    for j in range(0, len(freqRanges)):
        labelUpVar, labelDownVar = StringVar(), StringVar()
        labelUp = Label(window, textvariable=labelUpVar)
        labelDown = Label(window, textvariable=labelDownVar)
        labelUpVar.set(getLabelName(freqRanges[j][0]))
        labelDownVar.set(getLabelName(freqRanges[j][1]))
        labels.append([labelUp, labelDown])
    # Master slider label
    labels.append(
        [Label(window, textvariable=StringVar(value='Master')), Label(window, textvariable=StringVar(value=''))])


def setMenu():
    # Main menu
    menu = Menu(window)
    window.config(menu=menu)

    # File menu
    filemenu = Menu(menu)
    menu.add_cascade(label='File', menu=filemenu)

    filemenu.add_command(label='Open...', accelerator='Command+O', command=loadAudioFile)
    window.bind_all("<Command-o>", loadAudioFile)

    filemenu.add_command(label='Open test sound', accelerator='Command+T', command=loadTestSound)
    window.bind_all("<Command-t>", loadTestSound)
    filemenu.add_separator()

    filemenu.add_command(label='Exit', accelerator='Command+W', command=quitApp)
    window.bind_all("<Command-w>", quitApp)

    # Track menu
    trackmenu = Menu(menu)
    menu.add_cascade(label='Track', menu=trackmenu)

    trackmenu.add_command(label='Play', accelerator='Command+P', command=playAudio)
    window.bind_all("<Command-p>", playAudio)

    trackmenu.add_command(label='Equalize', accelerator='Command+E', command=equalize)
    window.bind_all("<Command-e>", equalize)

    trackmenu.add_command(label='Reset', accelerator='Command+R', command=resetSliders)
    window.bind_all("<Command-r>", resetSliders)

    #  Presets menu
    presetsmenu = Menu(menu)
    menu.add_cascade(label='Presets', menu=presetsmenu)
    presetsmenu.add_command(label='Emphasize bass', accelerator='Command+B', command=emphBass)
    window.bind_all("<Command-b>", emphBass)
    presetsmenu.add_command(label='Emphasize midtones', accelerator='Command+N', command=emphMidtones)
    window.bind_all("<Command-n>", emphMidtones)
    presetsmenu.add_command(label='Emphasize treble', accelerator='Command+M', command=emphTreble)
    window.bind_all("<Command-m>", emphTreble)

    # Help menu
    helpmenu = Menu(menu)
    menu.add_cascade(label='Help', menu=helpmenu)
    helpmenu.add_command(label='About project', command=openURL)
    helpmenu.entryconfigure('About project', accelerator='Command+A')


def setWindowSize():
    screenwidth = window.winfo_screenwidth()
    windowHeight.set(400)
    if slidersNo.get() == 10:
        windowWidth.set(int(screenwidth * 0.6))
        sliderPadX.set(10)
        sliderWidth.set(15)
    elif slidersNo.get() == 31:
        windowWidth.set(max(1650, screenwidth))  # TODO ???
        sliderPadX.set(0)
        sliderWidth.set(1)
    window.minsize(windowWidth.get(), windowHeight.get())
    window.maxsize(windowWidth.get(), windowHeight.get())


def forgetGrid():
    for slider in sliders:
        slider.grid_forget()
    for label in labels:
        label[0].grid_forget()
        label[1].grid_forget()
    for inputField in inputFields:
        inputField.grid_forget()
    audiofileinfo.grid_forget()
    playButton.grid_forget()
    equalizeButton.grid_forget()
    resetButton.grid_forget()
    dialogue.grid_forget()
    buttonlabel.grid_forget()
    button10.grid_forget()
    button31.grid_forget()


def gridSliders():
    # i = 0
    # for slider in sliders:
    #     slider.scale.grid(row=1, column=i, padx=sliderPadX.get())
    for i in range(0, slidersNo.get()):
        labels[i][0].grid(row=0, column=i)
        sliders[i].grid(row=1, column=i, padx=sliderPadX.get())
        inputFields[i].grid(row=2, column=i)
        labels[i][1].grid(row=3, column=i)


def updateSlidersNo():
    setWindowSize()
    forgetGrid()  # Reset grid
    setSliders()
    gridSliders()
    gridLowerUI()
    dialoguestr.set('Changed number of bands to ' + str(slidersNo.get()) + '.')


def gridLowerUI():
    audiofileinfo.grid(row=4, column=0, columnspan=(slidersNo.get() - 3))
    playButton.grid(row=4, column=(slidersNo.get() - 2))
    equalizeButton.grid(row=4, column=(slidersNo.get() - 1))
    resetButton.grid(row=4, column=slidersNo.get())
    dialogue.grid(row=5, columnspan=5, padx=10, sticky=W)
    buttonlabel.grid(row=5, column=(slidersNo.get() - 2))
    button10.grid(row=5, column=(slidersNo.get() - 1))
    button31.grid(row=5, column=(slidersNo.get()))


def setEQ(vals):
    for i in range(0, slidersNo.get()):
        sliders[i].set(vals[i])


def emphBass(event=None):
    vals = []
    if slidersNo.get() == 10:
        vals = [6, 8, 10, 0, 0, 0, -2, -5, -9, -10]
    elif slidersNo.get() == 31:
        vals = []
    setEQ(vals)


def emphMidtones(event=None):
    vals = []
    if slidersNo.get() == 10:
        vals = [-3, -2, -1, 5, 8, 10, 5, 0, -1, -3]
    elif slidersNo.get() == 31:
        vals = []
    setEQ(vals)


def emphTreble(event=None):
    vals = []
    if slidersNo.get() == 10:
        vals = [-10, -8, -5, -1, 0, 0, 1, 5, 10, 10]
    elif slidersNo.get() == 31:
        vals = []
    setEQ(vals)


if __name__ == '__main__':
    # Initiate pygame mixer
    mixer.init()

    window = tk.Tk()
    window.title('Very cool equalizer')

    # Variables
    audiofilename = tk.StringVar()
    dialoguestr = tk.StringVar()
    audiodata = []
    slidersNo = tk.IntVar(value=10)
    windowWidth = tk.IntVar()
    windowHeight = tk.IntVar()
    sliderPadX = tk.IntVar()
    sliderWidth = tk.IntVar()
    freqRanges = getFreqRanges()

    # Constants
    amplifyFrom = 12  # in dB
    amplifyTo = -12
    freqMin = 20
    freqMax = 20000

    setWindowSize()

    # Set up window icon
    ico = Image.open('equalizer_icon.png')
    photo = ImageTk.PhotoImage(ico)
    window.wm_iconphoto(True, photo)
    window.option_add('*tearOff', FALSE)

    # Set up grid
    window.rowconfigure(0, weight=1)  # Spot for high-ends of scales
    window.rowconfigure(1, weight=2)  # Spot for scales
    window.rowconfigure(2, weight=1)  # Spot for precise dB modulation
    window.rowconfigure(3, weight=1)  # Spot for low-ends of scales
    window.rowconfigure(4, weight=1)  # Spot for additional stuff
    window.rowconfigure(5, weight=1)

    setMenu()

    # Slider-related stuff
    sliders = []
    inputFields = []
    labels = []

    setSliders()

    # Lower part of the GUI
    audiofileinfo = Label(window, textvariable=audiofilename)
    playButton = Button(window, text='Play', command=playAudio)
    equalizeButton = Button(window, text='Equalize', command=equalize)
    resetButton = Button(window, text='Reset', command=resetSliders)
    dialogue = Label(window, textvariable=dialoguestr)

    # Set up buttons for sliders amount
    buttonlabel = Label(window, text='Number of bands: ')
    button10 = Radiobutton(window, text="10", variable=slidersNo, value=10, command=updateSlidersNo)
    button31 = Radiobutton(window, text="31", variable=slidersNo, value=31, command=updateSlidersNo)

    # Grid everything
    gridSliders()
    gridLowerUI()

    window.mainloop()
