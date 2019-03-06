#creating individual , sorted datasets per dosage column 

import matplotlib.pyplot as plt
import numpy as np 
import pandas as pd
import matplotlib as mp
from mpl_toolkits import mplot3d
import csv
import math
from scipy.spatial import distance
from scipy.interpolate import interp1d

file = np.genfromtxt("datasets.csv",delimiter = ',')
x=file[:,0]
y=file[:,1]
z=file[:,2]
dose = file[:,3]
dose2 = file[:,4]
dose3 = file[:,5]
dose4 = file[:,6]
file = np.vstack((x,y,z,dose)).T
file = file[file[:,3].argsort()]
print(file)
np.savetxt("dose1d_1.csv",file,delimiter=',')

file = np.vstack((x,y,z,dose2)).T
file = file[file[:,3].argsort()]
print(file)
np.savetxt("dose1d_2.csv",file,delimiter=',')

file = np.vstack((x,y,z,dose3)).T
file = file[file[:,3].argsort()]
print(file)
np.savetxt("dose2d_1.csv",file,delimiter=',')

file = np.vstack((x,y,z,dose4)).T
file = file[file[:,3].argsort()]
print(file)
np.savetxt("dose3d_1.csv",file,delimiter=',')

#file = np.vstack((x,y,z,dose)).T

#np.savetxt("dose1d_1.csv",file,delimiter=',')
