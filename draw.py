import csv
import matplotlib.pyplot as plot

f=open('example.csv','r')
r=csv.reader(f)
x=[]
y=[]
counter=0
for i in r:
    break
for i in r:
    x[counter]=i[0]
    y[counter]=i[1]
    counter+=1

plot.plot(x,y)
plot.show()