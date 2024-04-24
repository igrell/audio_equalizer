import tkinter as tk
from tkinter import *
from tkinter import ttk, messagebox
from PIL import Image, ImageTk
import webbrowser

def openURL():
    webbrowser.open('https://github.com/igrell/audio_equalizer')

if __name__ == '__main__':
    window = tk.Tk()
    window.title('Equalizer')
    ico = Image.open('equalizer_icon.png')
    photo = ImageTk.PhotoImage(ico)
    window.wm_iconphoto(True, photo)
    window.option_add('*tearOff', FALSE)

    window_width, window_height = 600, 400

    window.minsize(window_width, window_height)
    window.maxsize(window_width, window_height)

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



    window.mainloop()