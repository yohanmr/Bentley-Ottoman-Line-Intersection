from matplotlib import pyplot as plt
import numpy as np

T=[]
lineSegments=[]
with open("lines.txt", "r") as file1:
    for line in file1.readlines():
        coordinateList = np.asarray([float(i) for i in line.split(" ")])
        startX = coordinateList[0]
        startY = coordinateList[1]
        endX = coordinateList[2]
        endY = coordinateList[3]
        line = np.array([[startX,startY],[endX,endY]])
        lineSegments.append(line)

lineSegments = np.array(lineSegments)

X=lineSegments[:,:,0].T
Y=lineSegments[:,:,1].T

xcor = []
ycor = []

with open("points.txt", "r") as file2:
    for point in file2.readlines():
        pointList = np.asarray([float(i) for i in point.split(" ")])
        xcor.append(pointList[0])
        ycor.append(pointList[1])

# set axes limits
axes = plt.gca()
axes.set_xlim([0,100])
axes.set_ylim([0,100])

plt.plot(X,Y,color="black",linewidth=0.7)
plt.plot(X,Y,'b.',linewidth=0.5)
plt.scatter(xcor, ycor, color="red",linewidth=0.5,marker='X')
plt.show()