import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl

file = open("Measure.txt")
mtps = np.loadtxt(file, delimiter=",")
row, col = mtps.shape

xmax, ymax, w, h = mtps.max(axis=0)

ax = plt.figure().add_subplot(111)
for i in range(row):
    rect = mpl.patches.Rectangle((mtps[i][0], mtps[i][1]),
                                 mtps[i][2], mtps[i][3],
                                 fill=None, color='red', linewidth='2')
    ax.add_patch(rect)
plt.xlim([-0, xmax + w + 1])
plt.ylim([-0, ymax + h + 1])
plt.grid()
plt.show()

ax = plt.figure().add_subplot(111)
for i in range(row):
    rect = mpl.patches.Rectangle((mtps[i][0], mtps[i][1]),
                                 mtps[i][2], mtps[i][3],
                                 color='red', linewidth='2')
    ax.add_patch(rect)
plt.xlim([-0, xmax + w + 1])
plt.ylim([-0, ymax + h + 1])
plt.grid()
plt.show()

file = open("ContourH.txt")
ctpsv = np.loadtxt(file, delimiter=",")
rowv, colv = ctpsv.shape
ax = plt.figure().add_subplot(111)
for i in range(rowv):
    plt.axhline(ctpsv[i][0], ctpsv[i][1] / (xmax + w + 1), ctpsv[i][2] / (xmax + w + 1),
                linewidth=2, color='green')

file1 = open("ContourV.txt")
ctpsh = np.loadtxt(file1, delimiter=",")
rowh, colh = ctpsh.shape
for i in range(rowh):
    plt.axvline(ctpsh[i][0], ctpsh[i][1] / (ymax + h + 1), ctpsh[i][2] / (ymax + h + 1),
                linewidth=2, color='blue')

plt.xlim([-0, xmax + w + 1])
plt.ylim([-0, ymax + h + 1])
plt.grid()
plt.show()
