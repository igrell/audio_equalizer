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


if __name__ == '__main__':
    # Constants
    windowWidth = 1000
    windowHeight = 400

    window = tk.Tk()
    window.title('Very cool equalizer')

    # Set constant window size
    window.minsize(windowWidth, windowHeight)
    window.maxsize(windowWidth, windowHeight)

    window.rowconfigure(0, weight=1)  # Spot for high-ends of scales
    window.rowconfigure(1, weight=2)  # Spot for scales

    slider = Scale(window, from_=-12, to=12, resolution=0.1, length=150,
                   width=15, showvalue=False)
    slider2 = Scale(window, from_=-12, to=12, resolution=0.1, length=150,
                    width=15, showvalue=True)
    slider.grid(row=0, column=0, padx=0)
    # slider2.grid(row=0, column=1, padx=0)

    window.mainloop()
