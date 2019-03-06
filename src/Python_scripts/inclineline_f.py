#Implementation in progress, devising functions for inclined line, dose verificationg and solving

import matplotlib.pyplot as plt
import numpy as np 
import pandas as pd
import matplotlib as mp
from mpl_toolkits import mplot3d
import csv
import math
from scipy.spatial import distance
from scipy.interpolate import interp1d
from numpy import genfromtxt

coord = np.genfromtxt('coord.csv',delimiter = ',')
x = coord[:,0]
y = coord[:,1]
z = coord[:,2]
print(coord)
print(coord.shape)
d = np.genfromtxt('dosel.csv',delimiter=',')
print(d.shape)
c1=50
l=55
cnst=4*(math.pi)
m=np.sqrt(x**2+y**2+z**2)
k1=c1/cnst
k2=c1/m**2
k3=k1/(3*(m**3))
k4=(d-k2)/k3
k5=(l**2-k4)/3

l11=(l-np.sqrt(l**2 - (4*k5)))/2
print(l11)
l2=l-l11
print(l2)
l_l = l11 + l2
print(l_l)


#term1=np.arctan(l1/r)+np.arctan(l2/r)

#dose = c1 * term1 /(cnst )