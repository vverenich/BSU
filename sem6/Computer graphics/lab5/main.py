import sdl2.ext
import matplotlib.pyplot as plt
from matplotlib.path import Path
from matplotlib.patches import PathPatch
import tkinter as tk
from SH import PolygonClipper

def liang():
    lines = []

    with open('D:\program etc\projects3\cgcgcg\lab5\input1.txt', 'r') as f:
        N = int(f.readline())    
        for i in range(N):
            x1, y1, x2, y2 = map(int, f.readline().split())
            lines.append((x1, y1, x2, y2))

        x_min, y_min, x_max, y_max = map(int, f.readline().split())

    fig, ax = plt.subplots()

    ax.plot([x_min, x_max], [y_min, y_min], color='blue', linewidth=3)
    ax.plot([x_min, x_max], [y_max, y_max], color='blue', linewidth=3)
    ax.plot([x_min, x_min], [y_min, y_max], color='blue', linewidth=3)
    ax.plot([x_max, x_max], [y_min, y_max], color='blue', linewidth=3)

    for line in lines:
        x1, y1, x2, y2 = line
        ax.plot([x1, x2], [y1, y2], color='black', linewidth=2)

    ax.spines['left'].set_position('zero')
    ax.spines['bottom'].set_position('zero')
    ax.spines['right'].set_color('none')
    ax.spines['top'].set_color('none')

    ax.xaxis.set_major_locator(plt.MultipleLocator(1))
    ax.yaxis.set_major_locator(plt.MultipleLocator(1))
    ax.grid(which='major', color='gray', linestyle='--')

    for line in lines:
        x1, y1, x2, y2 = line
        line = sdl2.ext.algorithms.liangbarsky(x_min, y_max, x_max, y_min, x1, y1, x2, y2)
        ax.plot([line[0], line[2]], [line[1], line[3]], color='red', linewidth=3)

    def onscroll(event):
        step = 1 if event.button == 'up' else -1
        ax.set_xlim(ax.get_xlim()[0] - step, ax.get_xlim()[1] + step)
        ax.set_ylim(ax.get_ylim()[0] - step, ax.get_ylim()[1] + step)
        plt.draw()

    fig.canvas.mpl_connect('scroll_event', onscroll)

    plt.show()


def hodgman():
    polygon1 = []
    polygon2 = []

    with open('D:\program etc\projects3\cgcgcg\lab5\input2.txt', 'r') as f:
        n1 = int(f.readline())    
        for i in range(n1):
            x1, y1 = map(int, f.readline().split())
            polygon1.append((x1, y1))

        n2 = int(f.readline())    
        for i in range(n2):
            x1, y1 = map(int, f.readline().split())
            polygon2.append((x1, y1))

    polygon_path_1 = Path(polygon1)
    polygon_patch_1 = PathPatch(polygon_path_1, facecolor='blue', edgecolor='blue')
    polygon_path_2 = Path(polygon2)
    polygon_patch_2 = PathPatch(polygon_path_2, facecolor='pink', edgecolor='pink')
    fig, ax = plt.subplots()
    ax.add_patch(polygon_patch_1)
    ax.add_patch(polygon_patch_2)
    ax.spines['left'].set_position('zero')
    ax.spines['bottom'].set_position('zero')
    ax.spines['right'].set_color('none')
    ax.spines['top'].set_color('none')
    ax.set_xlim(min(x for x, y in polygon1 + polygon2) - 1, max(x for x, y in polygon1 + polygon2) + 1)
    ax.set_ylim(min(y for x, y in polygon1 + polygon2) - 1, max(y for x, y in polygon1 + polygon2) + 1)

    ax.xaxis.set_major_locator(plt.MultipleLocator(1))
    ax.yaxis.set_major_locator(plt.MultipleLocator(1))
    ax.grid(which='major', color='gray', linestyle='--')

    clip = PolygonClipper(warn_if_empty = False)

    clipped_polygon = clip(polygon1,polygon2)
    polygon_path_3 = Path(clipped_polygon)
    polygon_patch_3 = PathPatch(polygon_path_3, facecolor='purple', edgecolor='purple')
    ax.add_patch(polygon_patch_3)

    def onscroll(event):
        step = 1 if event.button == 'up' else -1
        ax.set_xlim(ax.get_xlim()[0] - step, ax.get_xlim()[1] + step)
        ax.set_ylim(ax.get_ylim()[0] - step, ax.get_ylim()[1] + step)
        plt.draw()

    fig.canvas.mpl_connect('scroll_event', onscroll)

    plt.show()


def show_graph_window():
    root = tk.Tk()
    root.title("ho ho ho")

    liang_button = tk.Radiobutton(root, text="liang-barsky", value=1, command=lambda: liang())
    liang_button.pack()

    rebuild_button = tk.Radiobutton(root, text="sutherland-hodgman", value=2, command=lambda: hodgman())
    rebuild_button.pack()
    plt.show()

    root.mainloop()

show_graph_window()