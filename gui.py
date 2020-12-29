import tkinter as tk 
from tkinter import ttk 
from tkinter import filedialog as fd
import cv2
from idp import *
# Creating tkinter window 
window = tk.Tk() 
window.title('haas tools') 
window.geometry('500x250') 


# label text for title 
ttk.Label(window, text = "Image Tools", 
		background = 'green', foreground ="white", 
		font = ("Times New Roman", 15)).grid(row = 0, column = 1) 

joke = tk.StringVar()
btn = ttk.Button(window, text ='Open',command = lambda:io()).grid(column = 2 ,row =10 )

ttk.Label(window, text = "Open the file :",  
		font = ("Times New Roman", 10)).grid(column=0,row=10,padx=10,pady=10)

input_text = tk.StringVar() 
filename =''
entry1 = ttk.Entry(window, textvariable= joke ,width =27)
entry1.grid(column = 1 ,row =10) 

# label 
ttk.Label(window, text = "Select the tool :", 
		font = ("Times New Roman", 10)).grid(column = 0, 
		row = 15, padx = 10, pady = 25) 

# Combobox creation 
n = tk.StringVar() 
toolchoosen = ttk.Combobox(window, width = 27, textvariable = n) 

btn1 = ttk.Button(window, text ='Ok',command = lambda:go()).grid(column = 5 ,row =25 )
def io():
    filename = tk.filedialog.askopenfilename()
    joke.set(filename)

# Adding combobox drop down list 
toolchoosen['values'] = ('original', 
						'laplacian', 
						'Canny', 
						'numberplate', 
						'pencil' 
						) 

toolchoosen.grid(column = 1, row = 15) 
toolchoosen.current()

def go():
	if toolchoosen.get()=="original":
		original(entry1.get())
	elif toolchoosen.get()=="Canny":
		Canny(entry1.get())
	elif toolchoosen.get()=="laplacian":
		laplacian(entry1.get())
	elif toolchoosen.get()=="pencil":
		pencil(entry1.get())
	elif toolchoosen.get()=="numberplate":
		numberplate(entry1.get())
# loop ing main loop
window.mainloop()
