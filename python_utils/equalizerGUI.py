import os
import tkinter as tk
from tkinter import *
from tkinter import filedialog as fd
import numpy as np
from PIL import Image, ImageTk
import webbrowser
import contextlib

with contextlib.redirect_stdout(None):  # Hide pygame welcome prompt
    from pygame import mixer, event


# from playsound import playsound  # alternative to pygame for playing audio; seems outdated

def openURL():
    webbrowser.open('https://github.com/igrell/audio_equalizer')


def getFreqRanges(_slidersNo):
    _freqMin, _freqMax = 20, 20000
    if _slidersNo == 10:  # ISO standard for 10 bands
        _freqRanges = [20, 40, 80, 160, 320, 640, 1280, 2560, 5120, 10240, 20000]
    elif _slidersNo == 31:  # ISO standard for 31 bands
        _freqRanges = [20, 25, 31.5, 40, 50, 63, 80, 100, 125, 160, 200, 250, 315, 400, 500, 630, 800, 1000, 1250, 1600,
                       2000, 2500, 3150, 4000, 5000, 6300, 8000, 10000, 12500, 16000, 20000]
    else:
        _freqRanges = np.linspace(_freqMin, _freqMax, _slidersNo + 1)  # if no standard applies, make bandwidth constant
    return _freqRanges


def getLabelName(freq):
    if freq < 1000.0:
        return str(int(freq)) + ' Hz'
    else:
        return str(round(freq / 1000, 1)) + ' kHz'


def correlateValues(scale, inputField):
    scale.set(inputField.get("1.0", "end-1c"))
    window.after(1, correlateValues)


def loadAudioFile(event=None):
    audiofilename.set(fd.askopenfilename())
    if audiofilename.get() != '':
        filetype = audiofilename.get().split('.')[1]
        if filetype != 'wav':
            print('Wrong filetype! Please insert a WAV file')
            return None
        else:
            print('Loaded audio file: ', audiofilename.get().split('/')[-1])
            return audiofilename


def quitApp(event=None):  # TODO this needn't be here
    window.quit()


def playAudio():  # TODO show 'play' again when audio finishes
    mixer.music.load(audiofilename.get())
    if playButton["text"] == "Play":
        playButton["text"] = "Pause"
        mixer.music.play()
    else:
        playButton["text"] = "Play"
        mixer.music.pause()

    # playsound(audioFilename.get())

def equalize():
    pass

def getSliderWidth(_slidersNo):
    if _slidersNo == 31:
        return 7
    else:
        return 15


if __name__ == '__main__':
    # Constants
    slidersNo = 10
    sliderWidth = getSliderWidth(slidersNo)
    scaleWidth = sliderWidth + 100  # adds width of the counter
    amplifyFrom = 12
    amplifyTo = -12
    freqMin = 20
    freqMax = 20000
    windowWidth = 1000
    windowHeight = 400
    sliderPadX = 20
    # sliderPadX = 0.5 * ((windowWidth / slidersNo) - scaleWidth)  # TODO

    # Initiate pygame mixer
    mixer.init()

    window = tk.Tk()
    window.title('Very cool equalizer')

    # Set constant window size
    window.minsize(windowWidth, windowHeight)
    window.maxsize(windowWidth, windowHeight)

    # Variables
    audiofilename = tk.StringVar()
    audiodata = []

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

    # Menu
    menu = Menu(window)
    window.config(menu=menu)

    # File menu
    filemenu = Menu(menu)
    menu.add_cascade(label='File', menu=filemenu)
    filemenu.add_command(label='Open...', accelerator='Command+O', command=loadAudioFile)
    window.bind_all("<Command-o>", loadAudioFile)
    filemenu.add_separator()
    filemenu.add_command(label='Exit', accelerator='Command+W', command=quitApp)
    window.bind_all("<Command-w>", quitApp)

    # Help menu
    helpmenu = Menu(menu)
    menu.add_cascade(label='Help', menu=helpmenu)
    helpmenu.add_command(label='About project', command=openURL)
    helpmenu.entryconfigure('About project', accelerator='Command+A')

    # Slider-related stuff
    sliders = []
    inputFields = []
    labels = []

    # Initialize sliders
    for i in range(0, slidersNo):
        sliderVar = tk.DoubleVar(value=0.0)
        slider = Scale(window, from_=amplifyFrom, to=amplifyTo, variable=sliderVar, resolution=0.1, length=150,
                       width=sliderWidth, showvalue=True)
        inputField = Entry(window, width=4, textvariable=sliderVar)
        slider.set((amplifyFrom + amplifyTo) / 2)
        sliders.append(slider)
        inputFields.append(inputField)

    # Frequency ranges for sliders
    freqRanges = getFreqRanges(slidersNo)
    for i in range(0, len(freqRanges) - 1):
        labelUpVar, labelDownVar = StringVar(), StringVar()
        labelUp = Label(window, textvariable=labelUpVar)
        labelDown = Label(window, textvariable=labelDownVar)
        labelUpVar.set(getLabelName(freqRanges[i]))
        labelDownVar.set(getLabelName(freqRanges[i + 1]))
        labels.append([labelUp, labelDown])

    # Lower part of the GUI
    text = Label(window, textvariable=audiofilename)
    playButton = Button(window, text='Play', command=playAudio)
    equalizeButton = Button(window, text='Apply changes', command=equalize)

    # Grid everything
    for i in range(0, slidersNo):
        labels[i][0].grid(row=0, column=i)
        sliders[i].grid(row=1, column=i, padx=sliderPadX)
        inputFields[i].grid(row=2, column=i)
        labels[i][1].grid(row=3, column=i)
    text.grid(row=4, column=0, columnspan=(slidersNo - 3))
    playButton.grid(row=4, column=(slidersNo - 3))
    equalizeButton.grid(row=4, column=(slidersNo - 2), columnspan=2)

    window.mainloop()
