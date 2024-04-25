import tkinter as tk
from tkinter import *
import numpy as np
from PIL import Image, ImageTk
import webbrowser


def openURL():
    webbrowser.open('https://github.com/igrell/audio_equalizer')


def getFreqRanges(bandsNo):
    freqMin, freqMax = 20, 20000
    if bandsNo == 10:  # ISO standard for 10 bands
        freqRanges = [20, 40, 80, 160, 320, 640, 1280, 2560, 5120, 10240, 20000]
    elif bandsNo == 31:  # ISO standard for 31 bands
        freqRanges = [20, 25, 31.5, 40, 50, 63, 80, 100, 125, 160, 200, 250, 315, 400, 500, 630, 800, 1000, 1250, 1600,
                      2000, 2500, 3150, 4000, 5000, 6300, 8000, 10000, 12500, 16000, 20000]
    else:
        freqRanges = np.linspace(freqMin, freqMax, bandsNo + 1)  # if no standard applies, make bandwidth constant
    return freqRanges


def getLabelName(freq):
    if freq < 1000.0:
        return str(int(freq)) + ' Hz'
    else:
        return str(round(freq / 1000, 1)) + ' kHz'


def correlateValues(scale, inputField):
    scale.set(inputField.get("1.0", "end-1c"))
    window.after(1, correlateValues)


if __name__ == '__main__':
    # Constants
    bandsNo = 10
    amplifyFrom = 12
    amplifyTo = -12
    freqMin = 20
    freqMax = 20000
    window_width = int((78 * bandsNo))  # scale window according to bandsNo; TODO improve
    window_height = 400

    window = tk.Tk()
    window.title('Very cool equalizer')

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

    # Menu
    menu = Menu(window)
    window.config(menu=menu)

    # File menu
    filemenu = Menu(menu)
    menu.add_cascade(label='File', menu=filemenu)
    filemenu.add_command(label='Open...')
    filemenu.entryconfigure('Open...', accelerator='Command+O')
    filemenu.add_separator()
    filemenu.add_command(label='Exit', command=window.quit)
    filemenu.entryconfigure('Exit', accelerator='Command+W')

    # Help menu
    helpmenu = Menu(menu)
    menu.add_cascade(label='Help', menu=helpmenu)
    helpmenu.add_command(label='About project', command=openURL)

    # Slider-related stuff
    sliders = []
    inputFields = []
    labels = []

    for i in range(0, bandsNo):
        sliderVar = tk.DoubleVar(value=0.0)
        scale = Scale(window, from_=amplifyFrom, to=amplifyTo, variable=sliderVar, resolution=0.1, length=150, showvalue=True)
        inputField = Entry(window, width=4, textvariable=sliderVar)
        scale.set((amplifyFrom + amplifyTo) / 2)
        sliders.append(scale)
        inputFields.append(inputField)

    # Frequency ranges for sliders
    freqRanges = getFreqRanges(bandsNo)
    for i in range(0, len(freqRanges) - 1):
        labelUpVar, labelDownVar = StringVar(), StringVar()
        labelUp = Label(window, textvariable=labelUpVar)
        labelDown = Label(window, textvariable=labelDownVar)
        labelUpVar.set(getLabelName(freqRanges[i]))
        labelDownVar.set(getLabelName(freqRanges[i + 1]))
        labels.append([labelUp, labelDown])

    # Grid sliders
    for i in range(0, bandsNo):
        labels[i][0].grid(row=0, column=i)
        sliders[i].grid(row=1, column=i, padx=10)
        inputFields[i].grid(row=2, column=i)
        labels[i][1].grid(row=3, column=i)

    # Set constant window size
    window.minsize(window_width, window_height)
    window.maxsize(window_width, window_height)

    window.mainloop()
