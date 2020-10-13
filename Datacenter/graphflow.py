#!/usr/bin/python3
import matplotlib
matplotlib.use('Agg')
import numpy as np
import matplotlib.pyplot as plt
import os
import sys

# ToDay = sys.argv[1]
Completion_Scale = [0,100]


# DIR="Result/" + str(ToDay) + "/"

Chager_y = []
Chager_y.append(0)
fp = open("UpdateTimeout.txt","r")
lines = fp.readlines()
rows = len(lines)
result  = 0
for i in lines:
    result += int(i)
result = result / rows #avg
result = result / 1000 #ms
Chager_y.append(result)

# Charging Scale => 1
plt.xlabel('Time(ms)')
plt.ylabel('Completion(%)')
lines = plt.plot(Chager_y,Completion_Scale,'bo')
plt.setp(lines, color='r', linewidth=2.0)
lines = plt.plot(Chager_y,Completion_Scale)
plt.setp(lines, color='r', linewidth=2.0)
plt.savefig("15000flow.png")
plt.close()