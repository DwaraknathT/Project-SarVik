#Implementation in progress, reverse derivation of displacement(m) for line source

import matplotlib.pyplot as plt
import numpy as np 
import pandas as pd
import matplotlib as mp
from mpl_toolkits import mplot3d
import csv
import math
from scipy.spatial import distance
from scipy.interpolate import interp1d

def linalg_norm(res,ref):
    a=res
    b=ref
    return np.linalg.norm(a-b, axis=1)

file=pd.read_csv("datasets.csv")
coord=file.values
x=coord[:,0]
y=coord[:,1]
z=coord[:,2]
dose = coord[:,3]
#print(type(x))
#ref = ([0,0,0])
#coord2d = np.vstack((x,y)).T
#print(coord2d)
#ref = ([0,0])
#k = linalg_norm(coord2d,ref)
#np.savetxt("coord2d.csv",coord2d)
r = np.sqrt((x-0.1)**2 + y**2)
h = ((z**2-z)*111/(dose-111))**(0.5)
#l=1
#s=c1/l
#print(s)
l1 = 1 - z
#print(l1)
l2 = z
#print(l2)
#cnst=4*(math.pi)
term1=np.arctan(l1/r)+np.arctan(l2/r)
term2=np.arctan(l1/h)+np.arctan(l2/h)
#print(term1)
dose=(111*term1/(r)).T
dose1=(111*term2/(h)).T
print(dose1)
print(dose)
np.savetxt("revcheck1d_1.csv",dose1,delimiter= ',')

#print(dose)
#dose = np.vstack((x,y,z,dose)).T
#np.savetxt("dosel.csv",dose,delimiter=',')