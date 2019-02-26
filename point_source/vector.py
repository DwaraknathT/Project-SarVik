from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np
from itertools import product, combinations


fig = plt.figure()
ax = fig.gca(projection='3d')
ax.set_aspect("equal")
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

# draw cube
r = [0,50]
for s, e in combinations(np.array(list(product(r, r, r))), 2):
    if np.sum(np.abs(s-e)) == r[1]-r[0]:
        ax.plot3D(*zip(s, e), color="b")

xyz = np.genfromtxt("coord.csv",delimiter = ',')
radv = np.genfromtxt("r.csv")
# draw sphere
u, v = np.mgrid[0:2*np.pi:20j, 0:np.pi:10j]
a = np.cos(u)*np.sin(v)
b = np.sin(u)*np.sin(v)
c = np.cos(v)
for i in range(10):
    u, v = np.mgrid[0:2*np.pi:20j, 0:np.pi:10j]
    x = a*radv[i] + xyz[i,0]
    y = b*radv[i] + xyz[i,1]
    z = c*radv[i] + xyz[i,2]
    ax.plot_wireframe(x, y, z, color="r",alpha = 0.1)

# draw a point
ax.scatter([0], [0], [0], color="g", s=100)

# draw a vector
from matplotlib.patches import FancyArrowPatch
from mpl_toolkits.mplot3d import proj3d


class Arrow3D(FancyArrowPatch):

    def __init__(self, xs, ys, zs, *args, **kwargs):
        FancyArrowPatch.__init__(self, (0, 0), (0, 0), *args, **kwargs)
        self._verts3d = xs, ys, zs

    def draw(self, renderer):
        xs3d, ys3d, zs3d = self._verts3d
        xs, ys, zs = proj3d.proj_transform(xs3d, ys3d, zs3d, renderer.M)
        self.set_positions((xs[0], ys[0]), (xs[1], ys[1]))
        FancyArrowPatch.draw(self, renderer)

a = Arrow3D([0, 1], [0, 1], [0, 1], mutation_scale=20,
            lw=1, arrowstyle="-|>", color="k")
ax.add_artist(a)
plt.show()
