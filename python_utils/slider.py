import tkinter as tk
from tkinter import *


class Slider:
    def __init__(self, window, sliderWidth, freqRange):
        self.var = tk.DoubleVar()
        self.slider = Scale(window, from_=12, to=-12, variable=self.var, resolution=0.1, length=150,
                            width=sliderWidth.get(), showvalue=True)
        self.inputField = Entry(window, width=4, textvariable=self.var)
        # self.slider.set(0.0)
        self.freqFrom = freqRange[0]
        self.freqTo = freqRange[1]
