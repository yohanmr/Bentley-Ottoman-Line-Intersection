import pygame
import math
import time
from decimal import Decimal
# import numpy as np

pygame.init()

## setting size of display window
display_width = 700
display_height = 500

## Defining colors to be used in the display
black = (0,0,0)
white = (200,200,200)
red = (200,0,0)
blue = (0,0,200)

## Initializing window display using pygame
gDisplay = pygame.display.set_mode((display_width,display_height))
pygame.display.set_caption('Line Intersection')

##This is the main loop which update the window
def loop():

	## list to store the end points of edges
	edges = []
	## Reading edges from file and storing in edges list
	with open("lines.txt", "r") as f: 
		lines = f.readlines()
		for line in lines:
			l1 = line.split(" ")
			l2 = []
			l2.append(int(Decimal(l1[0])))
			l2.append(int(Decimal(l1[1])))
			l2.append(int(Decimal(l1[2])))
			l211 = l1[3][0:-1]
			l2.append(int(Decimal(l211)))
			edges.append(l2)


	## list to store the vertices to be plot
	vertices = []
	## Reading vertices from file
	with open("points.txt", "r") as f: 
		lines = f.readlines()
		for line in lines:
			l1 = line.split(" ")
			l2 = []
			l2.append(int(Decimal(l1[0])))
			l211 = l1[1][0:-1]
			l2.append(int(Decimal(l211)))
			vertices.append(l2)	
			

	point_radius = 5

	## adjusting the coordinated of vertices to fill the whole screen and scatter properly

	gDisplay.fill(white)
	
	for edge in edges :
		edge[0] = edge[0]*6 + 50
		edge[2] = edge[2]*6 + 50
		edge[1] = 450 - edge[1]*4
		edge[3] = 450 - edge[3]*4
		pygame.draw.circle(gDisplay, blue, [edge[0], edge[1]], point_radius)
		pygame.draw.circle(gDisplay, blue, [edge[2], edge[3]], point_radius)
		pygame.draw.line(gDisplay, black, [edge[0], edge[1]], [edge[2], edge[3]], 2)
	pygame.display.update()

	for point in vertices :
		point[0] = point[0]*6 + 50
		point[1] = 450 - point[1]*4
		pygame.draw.circle(gDisplay, red, point, point_radius)

	pygame.display.update()
	
	## makes sure the display window closes on clicking cross button
	while True :
		for event in pygame.event.get() :
			if event.type == pygame.QUIT:
				pygame.quit();	

loop()