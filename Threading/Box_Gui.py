# import pygame 

# pygame.init()

# GameDisplay=pygame.display.set_mode((800,600))

# pygame.display.set_caption("BOX PLOT")

# import tkinter as tk
# from tkinter import ttk

# import numpy as np

import matplotlib.pyplot as plt

import matplotlib
matplotlib.axes.Axes.boxplot
matplotlib.pyplot.boxplot


# spread = np.random.rand(50) * 100
# center = np.ones(25) * 50
# flier_high = np.random.rand(10) * 100 + 100
# flier_low = np.random.rand(10) * -100
# data = np.concatenate((spread, center, flier_high, flier_low))




def main():

	file_name="Box_in.txt"

	file=open(file_name,"r")

	Data=[]
	lines = file.readlines()
	for i in range(0,len(lines)):
		line=lines[i]

		if(line.find('#')>=0):
			continue
		elif(line.find("?")>=0):
			Orig_Data=line.split('?')[1]

			for x in Orig_Data:
				 	if(x.find(" ")>=0 or x.find("\n")>=0):
				 		continue
				 	print (set(x))
				 	#print(x.find(" "))
				 	Data.append(float(x))	 
			print(Orig_Data)
			print(Data)

		#elif(line.find(':')>=0)

	# for line in file:
		
	# 	else:

	fig1, ax1 = plt.subplots()
	ax1.set_title('Basic Plot')
	ax1.boxplot(Data,vert=False)

	plt.show()


if __name__ == '__main__':
	main()


