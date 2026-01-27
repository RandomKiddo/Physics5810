"""
  file: hello_world_gui.py
  
  Python script to demonstrate a window with some text using
   the Tkinter toolkit.
   
  Programmer:  Dick Furnstahl  furnstahl.1@osu.edu

  Revision history:
      12/28/09  original Python version, from a demo program 
      12/20/21  converted to python 3
   
"""

from tkinter import *    # import all names from tkinter

# Create an instance of the class Tkinter.Tk
my_root_window = Tk()    # this is the top-level or "root" window

# Give it a label and invoke "pack" to put it in the root window 
label_1 = Label(my_root_window, text='Welcome, 5810 student!',  # changed from 'Hello' to 'Welcome'
               foreground="white", background="red")
label_1.pack()

# Change the font using config()
label_1.config(font=("Arial", 24, "italic"))  # font changes
      

# Start the "event loop" running, which waits for things to happen 
my_root_window.mainloop()  #    
