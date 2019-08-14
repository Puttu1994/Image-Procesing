
#!/usr/bin/env python
# coding: utf-8

# In[52]:


import numpy as np
import matplotlib.pyplot as plt
import math as mt
import matplotlib.pyplot as plt


# In[53]:


image = np.fromfile("hat.raw", dtype = 'uint8')
image = image.reshape((512,512))
image.shape


# In[54]:


plt.imshow(image,cmap=plt.cm.gray)


# In[55]:


newimage = np.zeros(np.shape(image))
for i in range(256):
    for j in range(0+i+1):
        newimage[i,j] = image[i,j]
count = -1
for i in range(256,512,1):
    count+=1
    for j in range(256-count,-1,-1):
        newimage[i,j] = image[i,j]
        


# In[56]:


plt.imshow(newimage,cmap=plt.cm.gray)


# In[ ]:





# In[57]:


point = [(256,256),(128,128),(384,126),(0,0),(256,0),(512,0)]


# In[58]:


pointarc = [(256,256),(128,128),(384,126),(0,0),(256,128),(512,0)]


# In[59]:


puv = np.asarray(pointarc)
puv = puv.T


# In[60]:


pointarr = np.array(point)
pointarr = pointarr.T


# In[61]:


pointarr


# In[62]:


inv = np.ones((6,6))


# In[63]:


inv[1,:] = pointarr[0]
inv[2,:] = pointarr[1]
inv[3,:] = np.power(pointarr[0],2)
inv[4,:] = (pointarr[0]*pointarr[1])
inv[5,:] = np.power(pointarr[1],2)


# In[64]:


coeff = np.matmul(puv,np.linalg.inv(inv))


# In[65]:


newimage1 = np.zeros(np.shape(image))
for i in range(256):
    for j in range(0+i+1):
        coordmat = np.ones((6,1))
        coordmat[1,:] = i
        coordmat[2,:] = j
        coordmat[3,:] = np.power(i,2)
        coordmat[4,:] = i*j
        coordmat[5,:] = np.power(j,2)
        temp = np.matmul(coeff,coordmat)
#         newimage1[i,j] = newimage[int(temp[0,:]),int(temp[1,:])]
        newimage1[int(temp[0,:]),int(temp[1,:])] = newimage[i,j]
count = -1
for i in range(256,512,1):
    count+=1
    for j in range(256-count,-1,-1):
        coordmat = np.ones((6,1))
        coordmat[1,:] = i
        coordmat[2,:] = j
        coordmat[3,:] = np.power(i,2)
        coordmat[4,:] = i*j
        coordmat[5,:] = np.power(j,2)
        temp = np.matmul(coeff,coordmat)
        newimage1[int(temp[0,:]),int(temp[1,:])] = newimage[i,j]


# In[66]:


plt.imshow(newimage1,cmap=plt.cm.gray)


# In[67]:


for i in range(256):
    for j in range(0+i+1):
        newimage[i,511-j] = image[i,511-j]
count = -1
for i in range(256,512,1):
    count+=1
    for j in range(256+count,512,1):
        newimage[i,j] = image[i,j]
        


# In[68]:


plt.imshow(newimage,cmap=plt.cm.gray)


# In[69]:


point2 = [(256,256),(384,384),(128,384),(512,512),(256,512),(0,512)]
pointarc2 = [(256,256),(384,384),(128,384),(512,512),(256,384),(0,512)]

puv2 = np.asarray(pointarc2)
puv2 = puv2.T

pointarr2 = np.array(point2)
pointarr2 = pointarr2.T

inv2 = np.ones((6,6))

inv2[1,:] = pointarr2[0]
inv2[2,:] = pointarr2[1]
inv2[3,:] = np.power(pointarr2[0],2)
inv2[4,:] = (pointarr2[0]*pointarr2[1])
inv2[5,:] = np.power(pointarr2[1],2)

coeff2 = np.matmul(puv2,np.linalg.pinv(inv2))


# In[70]:


for i in range(256):
    for j in range(0+i+1):
        coordmat = np.ones((6,1))
        coordmat[1,:] = i
        coordmat[2,:] = 511-j
        coordmat[3,:] = np.power(i,2)
        coordmat[4,:] = i*(511-j)
        coordmat[5,:] = np.power(511-j,2)
        temp = np.matmul(coeff2,coordmat)
        if int(temp[0,:])>=0 and int(temp[0,:])<512 and int(temp[1,:])>=0 and int(temp[1,:])<512:
            newimage1[int(temp[0,:]),int(temp[1,:])] = newimage[i,511-j]
count = -1
for i in range(256,512,1):
    count+=1
    for j in range(256+count,512,1):
        coordmat = np.ones((6,1))
        coordmat[1,:] = i
        coordmat[2,:] = j
        coordmat[3,:] = np.power(i,2)
        coordmat[4,:] = i*(j)
        coordmat[5,:] = np.power(j,2)
        temp = np.matmul(coeff2,coordmat)
        if int(temp[0,:])>=0 and int(temp[0,:])<512 and int(temp[1,:])>=0 and int(temp[1,:])<512:
            newimage1[int(temp[0,:]),int(temp[1,:])] = newimage[i,j]


# In[71]:


plt.imshow(newimage1,cmap=plt.cm.gray)


# In[72]:


def spatialWarpCoeff(triangularPoints,warpedPoints):
#     # point2 = [(256,256),(128,384),(384,384),(512,512),(256,512),(512,512)]
#     point2 = [(256,256),(384,384),(128,384),(512,512),(256,512),(0,512)]

#     # pointarc2 = [(256,256),(128,384),(384,384),(512,512),(256,384),(512,512)]
#     pointarc2 = [(256,256),(384,384),(128,384),(512,512),(256,384),(0,512)]

    puv = np.asarray(warpedPoints)
    puv = puv.T

    pointarr = np.array(triangularPoints)
    pointarr = pointarr.T

    inv = np.ones((6,6))

    inv[1,:] = pointarr[0]
    inv[2,:] = pointarr[1]
    inv[3,:] = np.power(pointarr[0],2)
    inv[4,:] = (pointarr[0]*pointarr[1])
    inv[5,:] = np.power(pointarr[1],2)

#     coeff = np.matmul(puv2,np.linalg.pinv(inv2))
    return np.matmul(puv,np.linalg.pinv(inv))


# In[73]:


point = [(256,256),(128,128),(384,126),(0,0),(256,0),(512,0)]
pointarc = [(256,256),(128,128),(384,126),(0,0),(256,128),(512,0)]

coeff = spatialWarpCoeff(point,pointarc)
newimage1 = np.zeros(np.shape(image))
for i in range(256):
    for j in range(0+i+1):
        coordmat = np.ones((6,1))
        coordmat[1,:] = i
        coordmat[2,:] = j
        coordmat[3,:] = np.power(i,2)
        coordmat[4,:] = i*j
        coordmat[5,:] = np.power(j,2)
        temp = np.matmul(coeff,coordmat)
#         newimage1[i,j] = newimage[int(temp[0,:]),int(temp[1,:])]
        newimage1[int(temp[0,:]),int(temp[1,:])] = newimage[i,j]
count = -1
for i in range(256,512,1):
    count+=1
    for j in range(256-count,-1,-1):
        coordmat = np.ones((6,1))
        coordmat[1,:] = i
        coordmat[2,:] = j
        coordmat[3,:] = np.power(i,2)
        coordmat[4,:] = i*j
        coordmat[5,:] = np.power(j,2)
        temp = np.matmul(coeff,coordmat)
        newimage1[int(temp[0,:]),int(temp[1,:])] = newimage[i,j]
plt.imshow(newimage1,cmap=plt.cm.gray)


# In[74]:


point2 = [(256,256),(384,384),(128,384),(512,512),(256,512),(0,512)]
pointarc2 = [(256,256),(384,384),(128,384),(512,512),(256,384),(0,512)]
coeff = spatialWarpCoeff(point2,pointarc2)

for i in range(256):
    for j in range(0+i+1):
        coordmat = np.ones((6,1))
        coordmat[1,:] = i
        coordmat[2,:] = 511-j
        coordmat[3,:] = np.power(i,2)
        coordmat[4,:] = i*(511-j)
        coordmat[5,:] = np.power(511-j,2)
        temp = np.matmul(coeff2,coordmat)
        if int(temp[0,:])>=0 and int(temp[0,:])<512 and int(temp[1,:])>=0 and int(temp[1,:])<512:
            newimage1[int(temp[0,:]),int(temp[1,:])] = newimage[i,511-j]
count = -1
for i in range(256,512,1):
    count+=1
    for j in range(256+count,512,1):
        coordmat = np.ones((6,1))
        coordmat[1,:] = i
        coordmat[2,:] = j
        coordmat[3,:] = np.power(i,2)
        coordmat[4,:] = i*(j)
        coordmat[5,:] = np.power(j,2)
        temp = np.matmul(coeff2,coordmat)
        if int(temp[0,:])>=0 and int(temp[0,:])<512 and int(temp[1,:])>=0 and int(temp[1,:])<512:
            newimage1[int(temp[0,:]),int(temp[1,:])] = newimage[i,j]
plt.imshow(newimage1,cmap=plt.cm.gray)


# In[75]:


plt.imshow(newimage,cmap=plt.cm.gray)


# In[76]:


newimage3 = np.ones(image.shape)
count=-1
for i in range(256):
    count+=1
    for j in range(0+count,512-count,1):
        newimage3[i][j] = image[i][j]


# In[77]:


plt.imshow(newimage3,cmap=plt.cm.gray)


# In[78]:


point3 = [(256,256),(128,384),(128,128),(0,512),(0,256),(0,0)]
pointarc3 = [(256,256),(128,384),(128,128),(0,512),(128,256),(0,0)]

coeff = spatialWarpCoeff(point3,pointarc3)
newimage3 = np.ones(image.shape)
count=-1
for i in range(256):
    count+=1
    for j in range(0+count,512-count,1):
        coordmat = np.ones((6,1))
        coordmat[1,:] = i
        coordmat[2,:] = j
        coordmat[3,:] = np.power(i,2)
        coordmat[4,:] = i*j
        coordmat[5,:] = np.power(j,2)
        temp = np.matmul(coeff,coordmat)
        if int(temp[0,:])>=0 and int(temp[0,:])<512 and int(temp[1,:])>=0 and int(temp[1,:])<512:
            newimage1[int(temp[0,:]),int(temp[1,:])] = image[i][j]
plt.imshow(newimage1,cmap=plt.cm.gray)


# In[79]:


newimage3 = np.ones(image.shape)
count=-1
for i in range(256,512):
    count+=1
    for j in range(255-count,256+count,1):
        newimage3[i][j] = image[i][j]


# In[80]:


plt.imshow(newimage3,cmap=plt.cm.gray)


# In[81]:


point3 = [(256,256),(384,128),(384,384),(512,0),(512,256),(512,512)]
pointarc3 = [(256,256),(384,128),(384,384),(512,0),(384,256),(512,512)]

coeff = spatialWarpCoeff(point3,pointarc3)
newimage3 = np.ones(image.shape)
count=-1
for i in range(256,512):
    count+=1
    for j in range(255-count,256+count,1):
        coordmat = np.ones((6,1))
        coordmat[1,:] = i
        coordmat[2,:] = j
        coordmat[3,:] = np.power(i,2)
        coordmat[4,:] = i*j
        coordmat[5,:] = np.power(j,2)
        temp = np.matmul(coeff,coordmat)
        if int(temp[0,:])>=0 and int(temp[0,:])<512 and int(temp[1,:])>=0 and int(temp[1,:])<512:
            newimage1[int(temp[0,:]),int(temp[1,:])] = image[i][j]
plt.imshow(newimage1,cmap=plt.cm.gray)


# In[82]:


newimage3 = np.ones(image.shape)
count=-1
for j in range(0,256):
    count+=1
    for i in range(0+count,512-count,1):
        newimage3[i][j] = image[i][j]
plt.imshow(newimage3,cmap=plt.cm.gray)


# In[83]:


newimage3 = np.ones(image.shape)
count=-1
for j in range(256,512):
    count+=1
    for i in range(255-count,256+count,1):
        newimage3[i][j] = image[i][j]
plt.imshow(newimage3,cmap=plt.cm.gray)


# In[ ]:




