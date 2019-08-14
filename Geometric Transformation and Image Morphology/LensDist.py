
#!/usr/bin/env python
# coding: utf-8

# In[1]:


import numpy as np
import matplotlib.pyplot as plt
import math as mt


# In[2]:


image = np.fromfile("classroom.raw", dtype = 'uint8')
image = image.reshape((712,1072))
image.shape


# In[3]:


plt.imshow(image,cmap=plt.cm.gray)


# In[4]:


newimage = np.zeros((712,1072))


# In[5]:


k1 = -0.3536
k2 = 0.1730
k3 = 0

for i in range(image.shape[0]):
    for j in range(image.shape[1]):
        newx = (i-(image.shape[0]/2))/600
        newy = (j-(image.shape[1]/2))/600
        r = np.sqrt(np.power(newx,2)+np.power(newy,2))
        
        xCartesian = newx*(1+k1*np.power(r,2)+k2*np.power(r,4)+k3*np.power(r,6))
        yCartesian = newy*(1+k1*np.power(r,2)+k2*np.power(r,4)+k3*np.power(r,6))
#         print(xCartesian,yCartesian)
        
        xCartesian = (xCartesian*600)+(image.shape[0]/2)
        yCartesian = (yCartesian*600)+(image.shape[1]/2)

        if(xCartesian.round()>=0 and yCartesian.round()>=0 and (round(xCartesian))<712 and (round(yCartesian))<1072):                
                #print(xCartesian.round(),yCartesian.round())
            newimage[i,j] = image[(int(round(xCartesian))),int(round(yCartesian))]
        else:
            newimage[i,j] = 255


# In[6]:


plt.imshow(newimage,cmap=plt.cm.gray)


# In[7]:


plt.imsave("LenDistCorrected.jpg",newimage,cmap = plt.cm.gray)


# In[ ]:




