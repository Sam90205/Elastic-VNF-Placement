#!/usr/bin/python3
import matplotlib
matplotlib.use('Agg')
import numpy as np
import matplotlib.pyplot as plt
import os
import sys


fp = open("UpdateTimeout1000.txt","r")
lines = fp.readlines()
rows=len(lines)
datamat=np.zeros((rows,2))
row = 0

x_value = []
y_value = []

for i in lines:
    i = i.strip().split(' ')
    datamat[row,0] = str(i[0])
    datamat[row,1] = str(i[1])
    y_value.append(datamat[row,1])
    x_value.append(datamat[row,0])
    row+=1
fp.close()

plt.xlabel('Time(ms)')
plt.ylabel('Completion(%)')

line = plt.plot(y_value,x_value,'bo')
plt.setp(line, color='r', linewidth=2.0)
line = plt.plot(y_value,x_value)
plt.setp(line, color='r', linewidth=2.0)


fp = open("UpdateTimeout2000.txt","r")
lines = fp.readlines()
rows=len(lines)
datamat=np.zeros((rows,2))
row = 0

x_value1 = []
y_value1 = []

for i in lines:
    i = i.strip().split(' ')
    datamat[row,0] = str(i[0])
    datamat[row,1] = str(i[1])
    y_value1.append(datamat[row,1])
    x_value1.append(datamat[row,0])
    row+=1
fp.close()

plt.xlabel('Time(ms)')
plt.ylabel('Completion(%)')

line = plt.plot(y_value1,x_value1,'bo')
plt.setp(line, color='g', linewidth=2.0)
line = plt.plot(y_value1,x_value1)
plt.setp(line, color='g', linewidth=2.0)


fp = open("UpdateTimeout5000.txt","r")
lines = fp.readlines()
rows=len(lines)
datamat=np.zeros((rows,2))
row = 0

x_value2 = []
y_value2 = []

for i in lines:
    i = i.strip().split(' ')
    datamat[row,0] = str(i[0])
    datamat[row,1] = str(i[1])
    y_value2.append(datamat[row,1])
    x_value2.append(datamat[row,0])
    row+=1
fp.close()

line = plt.plot(y_value2,x_value2,'bo')
plt.setp(line, color='g', linewidth=2.0)
line = plt.plot(y_value2,x_value2)
plt.setp(line, color='g', linewidth=2.0)

fp = open("UpdateTimeout10000.txt","r")
lines = fp.readlines()
rows=len(lines)
datamat=np.zeros((rows,2))
row = 0

x_value3 = []
y_value3 = []

for i in lines:
    i = i.strip().split(' ')
    datamat[row,0] = str(i[0])
    datamat[row,1] = str(i[1])
    y_value3.append(datamat[row,1])
    x_value3.append(datamat[row,0])
    row+=1
fp.close()

line = plt.plot(y_value3,x_value3,'bo')
plt.setp(line, color='g', linewidth=2.0)
line = plt.plot(y_value3,x_value3)
plt.setp(line, color='g', linewidth=2.0)

plt.savefig("sample_test.png")
plt.close()
# plt.scatter(node_x, node_y)
# plt.savefig(DIR+str(num)+"/"+str(num)+"sample.png")