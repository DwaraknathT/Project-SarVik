
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

'''from mayavi import mlab
import numpy as np

[phi,theta] = np.mgrid[0:2*np.pi:12j,0:np.pi:12j]
x = np.cos(phi)*np.sin(theta)
y = np.sin(phi)*np.sin(theta)
z = np.cos(theta)

def plot_sphere(p):
    r,a,b,c = p
    return mlab.mesh(r*x+a, r*y+b, r*z+c)  


for k in range(200):
    c = np.random.rand(4)
    c[0] /= 10.
    plot_sphere(c)

mlab.show()'''

'''vc package '''


from mayavi import mlab
import numpy as np

csv_fn="coord.csv"
file=pd.read_csv("coord.csv",names=['x','y','z'])
res=file.values
#x=np.array(file.x)
#y=np.array(file.y)
#z=np.array(file.z)
#res = np.random.rand(200,3)
#res=np.res
csv1="dose.csv"
r=pd.read_csv(csv1,names=['dose'])
r=r.values

mlab.points3d(res[:,0],res[:,1],res[:,2],r)
mlab.show()