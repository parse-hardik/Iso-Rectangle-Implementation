import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl

file = open("Measure.txt")
mtps = np.loadtxt(file, delimiter=",")
row, col = mtps.shape

xmax, ymax, w, h = mtps.max(axis=0)
print(xmax, ymax)

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
    plt.axhline(ctpsv[i][0], ctpsv[i][1] / 16, ctpsv[i][2] / 16,
                linewidth=2, color='green')
    print(ctpsv[i][0], ctpsv[i][1], ctpsv[i][2])
plt.xlim([-0, xmax + w + 1])
plt.ylim([-0, ymax + h + 1])
plt.grid()
plt.show()
