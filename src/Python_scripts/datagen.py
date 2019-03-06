#random dataset generation

import matplotlib.pyplot as plt
import numpy as np 
import pandas as pd
import matplotlib as mp
from mpl_toolkits import mplot3d
import csv
import math
from scipy.spatial import distance
from scipy.interpolate import interp1d


x = np.random.randint(0,50,1000)
y = np.random.randint(0,50,1000)
z = np.random.randint(0,50,1000)

coord = np.vstack((x,y,z)).T 
np.savetxt("coord.csv",coord,delimiter = ',')

