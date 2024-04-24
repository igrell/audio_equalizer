import tkinter as tk
from tkinter import *
from tkinter import ttk, messagebox
import numpy as np
from PIL import Image, ImageTk
import webbrowser


def openURL():
    webbrowser.open('https://github.com/igrell/audio_equalizer')


def getFreqRanges(scalesNo):
    freqMin, freqMax = 20, 20000
    freqRanges = np.linspace(freqMin, freqMax, scalesNo + 1)  # TODO correct by appropriate function
    return freqRanges


def getLabelName(freq):
    if freq < 1000.0:
        return str(freq) + ' Hz'
    else:
        return str(round(freq / 1000, 1)) + ' kHz'

def getFreqLabels(freqRanges):
    labels = []
    for i in range(0, len(freqRanges) - 1):
        labelUpVar, labelDownVar = StringVar(), StringVar()
        labelUp = Label(window, textvariable=labelUpVar)
        labelDown = Label(window, textvariable=labelDownVar)
        labelUpVar.set(getLabelName(freqRanges[i]))
        labelDownVar.set(getLabelName(freqRanges[i + 1]))
        labels.append([labelUp, labelDown])
    return labels




def getScales(scalesNo):
    scales = []
    for i in range(0, scalesNo):
        fromVal = -12
        toVal = 12
        scale = Scale(window, from_=fromVal, to=toVal, resolution=0.1, length=150, showvalue=True)
        scale.set((fromVal + toVal) / 2)
        scales.append(scale)
    return scales


if __name__ == '__main__':
    window = tk.Tk()
    window.title('Equalizer')

    # Set up window icon
    ico = Image.open('equalizer_icon.png')
    photo = ImageTk.PhotoImage(ico)
    window.wm_iconphoto(True, photo)
    window.option_add('*tearOff', FALSE)

    # Set up grid
    window.rowconfigure(0, weight=1)  # Spot for high-ends of scales
    window.rowconfigure(1, weight=2)  # Spot for scales
    window.rowconfigure(2, weight=1)  # Spot for low-ends of scales
    window.rowconfigure(3, weight=1)  # Spot for buttons/etc.

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

    # Create scales with labels
    scalesNo = 15
    scales = getScales(scalesNo)
    freqRanges = getFreqRanges(scalesNo)
    labels = getFreqLabels(freqRanges)
    # Grid scales
    for i in range(0, scalesNo):
        labels[i][0].grid(row=0, column=i)
        scales[i].grid(row=1, column=i, padx=10)
        labels[i][1].grid(row=2, column=i)

    # Set constant window size
    window_width = int((80 * scalesNo))  # scale window according to scalesNo; TODO improve
    window_height = 400
    window.minsize(window_width, window_height)
    window.maxsize(window_width, window_height)

    window.mainloop()
