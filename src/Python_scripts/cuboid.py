#Confirmation of dose values for 3D, by using the obtained values, equations of edges

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
#print(type(x))
#ref = ([0,0,0])
#coord2d = np.vstack((x,y)).T
#print(coord2d)
#ref = ([0,0])
#k = linalg_norm(coord2d,ref)
#np.savetxt("coord2d.csv",coord2d)
r = np.sqrt((x)**2 + y**2)
r1 = np.sqrt((x-0.05)**2 + y**2)
r2 = np.sqrt((x)**2 + (y-0.05)**2)
r3 = np.sqrt((x-0.05)**2 + (y-0.05)**2)
#c1=(3.7*(10**10)*(2.2)*(10**(-6)))
#l=1
#s=c1/l
#print(s)
l1 = 1 - z
#print(l1)
l2 = 1 - l1
#print(l2)
#cnst=4*(math.pi)
term1=np.arctan(l1/r)+np.arctan(l2/r)
term2=np.arctan(l1/r1)+np.arctan(l2/r1)
term3=np.arctan(l1/r2)+np.arctan(l2/r2)
term4=np.arctan(l1/r3)+np.arctan(l2/r3)
#print(term1)
dose1=(111*term1/(r)).T
dose2=(111*term2/(r1)).T
dose3=(111*term3/(r2)).T
dose4=(111*term4/(r3)).T
dose = dose1[:,]+dose2[:,]+dose3[:,]+dose4[:,]
print(dose)
print(dose.shape)
#print(dose)
#dose = np.vstack((x,y,z,dose)).T
#np.savetxt("dosel.csv",dose,delimiter=',')