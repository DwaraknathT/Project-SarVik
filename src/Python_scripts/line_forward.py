#line_forward.py
#basic line_forward implementation for dose check

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

ref= np.array((0,0,0))

csv_fn="coord.csv"
file=pd.read_csv(csv_fn)
res=file.values
x=res[:,0] 
y=res[:,1]
z=res[:,2]
k=np.linalg.norm(res,ref)
k1=k**2
k2=k**4
c1=(3.7*(10**10)*(2.2)*(10**(-6)))
c2=5
l=4
s=c1*c2/l
l1=1
l2=3
li=l1+l2
l3=(l1*2)+(l2*2)-(l1*l2)
l3=-l3
s=s/li
cnst=4*(math.pi)
term1=np.arctan(l1/k1)+np.arctan(l2/k1)
dose=s*term1/(cnst*k1)

print(dose)

list=[]
for i in range(0,50):
	list.append(dose[i])
#print(dose)
#mp.plot(dose)
'''
k3=cnst*dose/s
k3=k3/li
#(1/k1)-(l3/k2)=k3 #equation for reverse.  we need to find k.

k3*k2-k1+l3=0

'''
