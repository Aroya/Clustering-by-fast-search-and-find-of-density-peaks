import csv
import matplotlib.pyplot as plot
import numpy as np
f=open('example0.csv','r')
r=csv.reader(f)
x=[]
y=[]
counter=0
for i in r:
    break
for i in r:
    x.append(float(i[0]))
    y.append(float(i[1]))

x1=x[:10]
y1=y[:10]
x2=x[11:]
y2=y[11:]

p1=plot.subplot(111)
p1.scatter(x1,y1,color='b')
p1.scatter(x2,y2,color='r')

plot.show()

f=open('output0.csv','r')
r=csv.reader(f)
x=[]
y=[]
counter=0
for i in r:
    break
for i in r:
    x.append(float(i[0]))
    y.append(float(i[1]))

x1=x[:9]
y1=y[:9]
x2=x[11:]
y2=y[11:]
x3=x[10:11]
y3=x[10:11]

p1=plot.subplot(111)
p1.scatter(x1,y1,color='b')
p1.scatter(x2,y2,color='r')
p1.scatter(x3,y3,color='y')

plot.show()