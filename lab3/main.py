import matplotlib.pyplot as plt
import numpy as np
from matplotlib.patches import Rectangle
import matplotlib.patches as mpatches
import time

def StepByStep(x1, y1, x2, y2):
    x_list = [x1, x2]
    y_list = [y1, y2]
    
    if x1 == x2:
        if y1 == y2:
            return x_array, y_array
        if y1 < y2:
            for i in range(y2 - y1):
                x_list.append(x1)
                y_list.append(y1 + i + 1)
            return x_list, y_list
        else:
            for i in range(y1 - y2):
                x_list.append(x1)
                y_list.append(y2 + i + 1)
            return x_list, y_list
    
    is_transposed = False
    if abs(y2 - y1) > abs(x2 - x1):
        is_transposed = True
        y1, y2, x1, x2 = x1, x2, y1, y2 

    if (x1 > x2):
        x1, x2 = x2, x1
        y1, y2 = y2, y1

    
    k = (y2 - y1) / (x2 - x1)
    b = y1 - k * x1
    step = abs(x2 - x1)
    d = (x2 - x1) / step
    is_less = x1 < x2

    while (is_less and x1 < x2) or (not is_less and x2 < x1):
        x1 += d
        y1 = k * x1 + b
        if not is_transposed:
            x_list.append(round(x1))
            y_list.append(round(y1))
        else:
            x_list.append(round(y1))
            y_list.append(round(x1))    
    
    return x_list, y_list

def plotLineLow(x0, y0, x1, y1):
    x_list = []
    y_list = []

    dx = x1 - x0
    dy = y1 - y0
    yi = 1
    if dy < 0:
        yi = -1
        dy = -dy
    D = (2 * dy) - dx
    y = y0

    for x in range(x0, x1 + 1, 1):
        x_list.append(x)
        y_list.append(y)
        if D > 0:
            y = y + yi
            D = D + (2 * (dy - dx))
        else:
            D = D + 2*dy
    
    return x_list, y_list

def plotLineHigh(x0, y0, x1, y1):
    x_list = []    
    y_list = []

    dx = x1 - x0
    dy = y1 - y0
    xi = 1
    if dx < 0:
        xi = -1
        dx = -dx
    D = (2 * dx) - dy
    x = x0

    for y in range(y0, y1 + 1, 1):
        x_list.append(x)
        y_list.append(y)
        if D > 0:
            x = x + xi
            D = D + (2 * (dx - dy))
        else:
            D = D + 2*dx
    
    return x_list, y_list

def Bresenham(x0, y0, x1, y1):
    if abs(y1 - y0) < abs(x1 - x0):
        if x0 > x1:
            return plotLineLow(x1, y1, x0, y0)
        else:
            return plotLineLow(x0, y0, x1, y1)
    else:
        if y0 > y1:
            return plotLineHigh(x1, y1, x0, y0)
        else:
            return plotLineHigh(x0, y0, x1, y1)


x0, y0, x1, y1 = map(int, input("Enter x0, y0, x1, y1\n").strip().split())

x_p = (x0, x1)
y_p = (y0, y1)

min_c = min(x0, y0, x1, y1)
max_c = max(x0, y0, x1, y1)

grid_size = max(abs(min_c), abs(max_c)) + 50

start = time.time()
x_s, y_s = StepByStep(x0, y0, x1, y1)
end = time.time()
print("Step by step: ", (end - start) / 1000.0)
start = time.time()
x_b, y_b = Bresenham(x0, y0, x1, y1)
end = time.time()
print("Bresenham: ", (end - start)/ 1000.0)

fig, ax = plt.subplots()

fig.canvas.manager.set_window_title("Basic Line Drawing Algorithms")

ax.plot()
ax.grid(True)
ax.set_aspect("equal")
red_patch = mpatches.Patch(color='red', label='Bresenham Algorithm')
blue_patch = mpatches.Patch(color='blue', label='Step by Step Algorithm')
ax.legend(handles=[red_patch, blue_patch])

plt.xticks(np.arange(-grid_size, grid_size, 1))
plt.yticks(np.arange(-grid_size, grid_size, 1))
plt.xlabel("x")
plt.ylabel("y", rotation=0)
for (x, y) in set(zip(x_b, y_b)):
    ax.add_patch(Rectangle((x - 0.5, y - 0.5), 1, 1, color='red', alpha=.3))
for (x, y) in set(zip(x_s, y_s)):
    ax.add_patch(Rectangle((x - 0.5, y - 0.5), 1, 1, color='blue', alpha=.3))

plt.plot(x_p, y_p, marker=",", color="black")
plt.show()
