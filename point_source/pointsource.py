import matplotlib.pyplot as plt
import numpy as np 
import pandas as pd
import matplotlib as mp
import csv
from scipy.spatial import distance
#from scipy.spatial.distance import euclidean
from scipy.interpolate import interp1d
'''from .geometry import (
    Transform, line_block_plane_collision,
    line_calc_limit_plane_collision, isocentre_plane_position
)'''
from scipy.interpolate import RegularGridInterpolator
'''import warnings
warnings.simplefilter(action='ignore', category=FutureWarning)'''
def linalg_norm(res,ref):
    a=res
    b=ref
    return np.linalg.norm(a-b, axis=1)

ref= np.array((0,0,0))
flux=100
energy=1.0
constant=flux*energy
'''with open('coord.csv') as csvfile:
    data = [(int(x), int(y), int(z)) for x, y, z in csv.reader(csvfile, delimiter= ',')]'''
csv_fn="coord.csv"
file=pd.read_csv(csv_fn)
res=file.values
'''new_column = file['dose'] + 1
# we then add the series to the dataframe, which holds our parsed CSV file
df['NewColumn'] = new_column
# save the dataframe to CSV
df.to_csv('path/to/file.csv', sep='\t')'''
dosage=constant/(linalg_norm(res,ref)**2)


'''with open('dose.csv', 'w') as csvFile:
    writer = csv.writer(csvFile)
    writer.writerows(my_iterator)

csvFile.close()'''
list=[]
print(dosage)
print(type(dosage))
for i in range(0,49):
	list.append(dosage[i])

np.savetxt('dose.csv',list,fmt='%.5f',delimiter=',',header='dose')
#print(list)

'''from visual import *
ball1=sphere(pos=vector(x,y,z),radius=radius,color=color)'''



'''def scipy_distance(data):
    a, b = data
    return list(map(distance.euclidean, a, b))


def mpl_dist(data):
    a, b = data
    return list(map(mp.mlab.dist, a, b))


def sqrt_einsum(data):
    a, b = data
    a_min_b = a - b
    return np.sqrt(np.einsum('ij,ij->i', a_min_b, a_min_b))'''




'''perfplot.show(
    setup=lambda n: np.random.rand(2, n, 3),
    n_range=[2**k for k in range(20)],
    kernels=[linalg_norm],
    logx=True,
    logy=True,
    xlabel='len(x), len(y)'
    )'''