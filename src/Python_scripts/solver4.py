##3D Source: Algorithm for 4th dataset, column 'G'
##Randomises number of datapoints

import math
import numpy as np 

file = np.genfromtxt("dose3d_1.csv",delimiter = ',')
x=file[:,0]
y=file[:,1]
z=file[:,2]
dosage = file[:,3]
num = 250
random = np.random.randint(0,1331,num)
#print(random)

a = []
b = []
c = []
d = []
for i in random:
	a.append(x[i])
	b.append(y[i])
	c.append(z[i])
	d.append(dosage[i])

data = np.vstack((a,b,c,d)).T
data = data[data[:,3].argsort()]
maxie = np.amax(data[:,3])
#print(data.shape)
#print(maxie)
a = []
b = []
c = []
d = []
i = num - 1
while(data[i][3] == maxie):
	a.append(data[i][0])
	b.append(data[i][1])
	c.append(data[i][2])
	d.append(data[i][3])
	i=i-1
#print(a)
#print(b)
#print(c)
#print(d)

#print(a)

a = np.asarray(a)
#print(a)
##print(a)
b = np.asarray(b)
#print(b)
c = np.asarray(c)
#print(c)
d = np.asarray(d)
#print(d)

xi = np.sum(a.dot(d.T))/np.sum(d)
yi = np.sum(b.dot(d.T))/np.sum(d)
zi = np.sum(c.dot(d.T))/np.sum(d)
coord = np.asarray([xi,yi,zi,num])
data = np.vstack((coord, data[data[:,0] < 4]))
print("Original 3D source is between planes x = 0.05 and x = 0 and y = 0 and y = 0.05")
print("New coordinate is: ")

print([xi,yi])

np.savetxt("newdata4.csv",data,delimiter=',')