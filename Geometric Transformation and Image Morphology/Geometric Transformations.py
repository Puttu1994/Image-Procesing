import numpy as np
import matplotlib.pyplot as plt
import math as mt


# In[376]:


image = np.fromfile("lighthouse1.raw", dtype = 'uint8')
image = image.reshape((256,256))
image.shape


# In[377]:


plt.imshow(image,cmap=plt.cm.gray)


# In[378]:


vertices = []
for i in range(image.shape[0]):
    for j in range(image.shape[1]):
        if i-1 >= 0 and j-1 >= 0 and j+1 < image.shape[1]:
#             print(image[i][j-1],image[i-1][j],image[i-1][j-1],image[i][j],(i,j))
            if image[i][j-1]==255 and image[i-1][j]==255 and image[i-1][j-1]==255 and image[i-1][j-1]==255 and image[i][j]!=255:
                vertices.append((i,j))


# In[379]:


verticesback = []
for i in range(image.shape[0]):
    for j in range(image.shape[1]-1,-1,-1):
        if i+1 <= 255 and j+1 <= 255 and j-1 < image.shape[1]:
#             print(image[i][j-1],image[i-1][j],image[i-1][j-1],image[i][j],(i,j))
            if image[i][j+1]==255 and image[i+1][j]==255 and image[i+1][j+1]==255 and image[i][j]!=255:
                verticesback.append((i,j))


# In[380]:


exact_edge = []
exact_edge.append(vertices[0])
exact_edge.append(vertices[-1])
exact_edge.append(verticesback[0])
exact_edge.append(verticesback[-1])


# In[381]:


exact_edge


# In[382]:


print(np.sqrt(np.power((119-182),2) + np.power((221-78),2)))
print(np.sqrt(np.power((80-223),2) + np.power((183-115),2)))
centerx = (exact_edge[1][0] + exact_edge[2][0])//2
centery = (exact_edge[1][1] + exact_edge[2][1])//2


# In[383]:


distx = abs(centerx - 128)
disty = abs(centery - 128)


# In[384]:


print(distx,disty)


# In[385]:


for i in range(image.shape[0]):
    for j in range(image.shape[1]):
        if(i>=exact_edge[0][0]):
            image[i-distx][j-disty] = image[i][j]
            image[i][j] = 255


# In[386]:


plt.imshow(image,cmap=plt.cm.gray)


# In[387]:


def rotateBack(imageCart,theta):
    out=np.zeros(imageCart.shape)
    for i in range(364):
        for j in range(364):
            x = 364/2-i;
            y = j - 364/2
            
            xCartesian = (x)*np.cos(np.deg2rad(theta)) + (y)*np.sin(np.deg2rad(theta))
            yCartesian = (x)*np.sin(np.deg2rad(theta)) - (y)*np.cos(np.deg2rad(theta))
            
            xCartesian = 128-xCartesian;
            yCartesian = yCartesian+128;
            
            if(xCartesian.round()>=0 and yCartesian.round()>=0 and xCartesian.round()<256 and yCartesian.round()<256):                
                #print(xCartesian.round(),yCartesian.round())
                out[i,j] = image[int(yCartesian.round()),int(xCartesian.round())]
    return out


# In[388]:


g=rotateBack(imageCart,-70)


# In[389]:


plt.imshow(g,cmap=plt.cm.gray)


# In[390]:


def rotateBack2(imageCart,theta):
    out=np.zeros(imageCart.shape)
    for i in range(256):
        for j in range(256):
            x = 256/2-i;
            y = j - 256/2
            
            xCartesian = (x)*np.cos(np.deg2rad(theta)) + (y)*np.sin(np.deg2rad(theta))
            yCartesian = (x)*np.sin(np.deg2rad(theta)) - (y)*np.cos(np.deg2rad(theta))
            
            xCartesian = 128-xCartesian;
            yCartesian = yCartesian+128;
            
            if(xCartesian.round()>=0 and yCartesian.round()>=0 and xCartesian.round()<256 and yCartesian.round()<256):                
                #print(xCartesian.round(),yCartesian.round())
                out[i,j] = image[int(yCartesian.round()),int(xCartesian.round())]
            else:
                out[i,j] = 255
    return out


# In[391]:


g=rotateBack2(image,theta-91)


# In[392]:


plt.imshow(g,cmap=plt.cm.gray)


# In[393]:


exact_edge


# In[394]:


num = 78 - 184
den = 184 - 221
theta = np.rad2deg(np.arctan(num/den))


# In[395]:


print(theta,num,den)


# In[396]:


xr1 = int(128-abs(num/2))
xr2 = int(128+abs(num/2))
yr1 = int(128-abs(num/2))
yr2 = int(128+abs(num/2))
nim = g[xr1:xr2,yr1:yr2]


# In[397]:


plt.imshow(nim,cmap=plt.cm.gray)


# In[398]:


target = np.fromfile("lighthouse.raw", dtype = 'uint8')
target = target.reshape((512,512))
target.shape


# In[399]:


plt.imshow(target,cmap=plt.cm.gray)


# In[400]:


Left = []
stop = 1
for i in range(110,332,1):
    if stop == 0: break
    for j in range(25,250,1):
        if target[i][j] == 255: 
            Left.append((i,j))
            stop = 0
            break

stop = 1
for i in range(350,288,-1):
    if stop == 0: break
    for j in range(25,250,1):
        if target[i][j] == 255: 
            Left.append((i,j))
            stop = 0
            break
            
        


# In[401]:


Left


# In[402]:


dist = Left[1][0] - Left[0][0]
print(dist)


# In[403]:


def scale(imageCart,scalefactor):
    out=np.zeros((160,160))
    for i in range(160):
        for j in range(160):
#             x = 160/2-i;
#             y = j - 160/2
            
            inv_scale = 1/scalefactor
            
            xCartesian = (i) * inv_scale
            yCartesian = (j) * inv_scale
            
#             xCartesian = 106/2-xCartesian;
#             yCartesian = yCartesian+106/2;
            
            if(round(xCartesian)>=0 and round(yCartesian)>=0 and round(xCartesian)<imageCart.shape[0] and round(yCartesian)<imageCart.shape[1]):                
                #print(xCartesian.round(),yCartesian.round())
                out[i,j] = imageCart[int(round(xCartesian)),int(round(yCartesian))]
            else:
                out[i,j] = 255
    return out


# In[404]:


s = scale(nim,160/nim.shape[0])


# In[405]:


plt.imshow(s,cmap=plt.cm.gray)


# In[406]:


t = target


# In[407]:


for i in range(s.shape[0]):
    for j in range(s.shape[1]):
        t[i+157][j+62] = s[i][j]


# In[408]:


plt.imshow(t,cmap = plt.cm.gray)
plt.imsave("Light1.raw",t,cmap = plt.cm.gray)
print(t.shape)


# In[409]:


image2 = np.fromfile("lighthouse2.raw", dtype = 'uint8')
image2 = image2.reshape((256,256))
plt.imshow(image2, cmap = plt.cm.gray)


# In[410]:


def rotateGeneral(imageCart,theta):
    out=np.zeros(imageCart.shape)
    for i in range(256):
        for j in range(256):
            x = 256/2-i;
            y = j - 256/2
            
            xCartesian = (x)*np.cos(np.deg2rad(theta)) + (y)*np.sin(np.deg2rad(theta))
            yCartesian = (x)*np.sin(np.deg2rad(theta)) - (y)*np.cos(np.deg2rad(theta))
            
            xCartesian = 128-xCartesian;
            yCartesian = yCartesian+128;
            
            if(xCartesian.round()>=0 and yCartesian.round()>=0 and xCartesian.round()<256 and yCartesian.round()<256):                
                #print(xCartesian.round(),yCartesian.round())
                out[i,j] = imageCart[int(yCartesian.round()),int(xCartesian.round())]
            else:
                out[i,j] = 255
    return out


# In[411]:


image = np.fromfile("lighthouse2.raw", dtype = 'uint8')
image = image.reshape((256,256))
plt.imshow(image, cmap = plt.cm.gray)

l2 = rotateGeneral(image,40)
plt.imshow(l2, cmap = plt.cm.gray)

flag1 = 0
for i in range(256):
    if flag1==1:
        break
    for j in range(256):
        if image[i][j]!=255:
            x1 = j
            y1 = i
            flag1 = 1
            break

print(x1,y1)

vertices = []
x=0
for i in range(l2.shape[0]):
    if x==2:break
    for j in range(l2.shape[1]):
        if i-1 >= 0 and j-1 >= 0 and j+1 < l2.shape[1]:
#             print(image[i][j-1],image[i-1][j],image[i-1][j-1],image[i][j],(i,j))
            if l2[i][j-1]==255 and l2[i-1][j]==255 and l2[i-1][j-1]==255 and l2[i][j]!=255:
                x = i
                vertices.append((i,j))
            if i==x:
                if l2[i][j]==255 and l2[i+1][j]==255:
                    x=2
                    vertices.append((i,j-1))
                    break;

verticesback = []
x=0
for i in range(255,188,-1):
    if x==2:break
    for j in range(l2.shape[0]):
        if i+1 <= 255 and j+1 <= 255 and j-1 < l2.shape[1]:
#             print(image[i][j-1],image[i-1][j],image[i-1][j-1],image[i][j],(i,j))
            if l2[i][j+1]==255 and l2[i+1][j]==255 and l2[i+1][j+1]==255 and l2[i][j]!=255:
                x = i
                verticesback.append((i,j))
            if i==x:
                if l2[i][j]==255 and l2[i-140][j]==255:
                    x=2
                    verticesback.append((i,j-1))
                    break;

exact_edge = []
exact_edge.append(vertices[0])
exact_edge.append(vertices[-1])
exact_edge.append(verticesback[0])
exact_edge.append(verticesback[-1])

exact_edge

plt.imshow(l2, cmap = plt.cm.gray)

print(np.sqrt(np.power((119-182),2) + np.power((221-78),2)))
print(np.sqrt(np.power((80-223),2) + np.power((183-115),2)))
centerx = (exact_edge[0][0] + exact_edge[3][0])//2
centery = (exact_edge[0][1] + exact_edge[3][1])//2

distx = abs(centerx - 128)
disty = abs(centery - 128)

print(distx,disty)

image2 = np.zeros(image.shape)
for i in range(image.shape[0]):
    for j in range(image.shape[1]):
        if(i>=exact_edge[0][0] and i+distx<256 and j+disty<256):
            image2[i-distx][j-disty] = l2[i][j]
            image2[i][j] = 255

plt.imshow(image2,cmap=plt.cm.gray)

num = 79 - 221
den = 184 - 221
xr1 = int(128-abs(num/2))
xr2 = int(128+abs(num/2))
yr1 = int(128-abs(num/2))
yr2 = int(128+abs(num/2))
nim = image2[xr1:xr2,yr1:yr2]
print(exact_edge)
plt.imshow(nim,cmap=plt.cm.gray)

s = scale(nim,160/nim.shape[0])


# In[412]:


plt.imshow(s, cmap = plt.cm.gray)


# In[413]:


Right = []
stop = 1
for i in range(0,100,1):
    if stop == 0: break
    for j in range(200,300,1):
        if target[i][j] == 255: 
            Right.append((i,j))
            stop = 0
            break

# stop = 1
# for i in range(200,288,-1):
#     if stop == 0: break
#     for j in range(25,250,1):
#         if target[i][j] == 255: 
#             Left.append((i,j))
#             stop = 0
#             break
            
        
print(Right)


# In[414]:


for i in range(s.shape[0]):
    for j in range(s.shape[1]):
        t[i+Right[0][0]][j+Right[0][1]] = s[i][j]


# In[415]:


plt.imshow(t, cmap = plt.cm.gray)


# In[416]:


image3 = np.fromfile("lighthouse3.raw", dtype = 'uint8')
image3 = image3.reshape((256,256))
image3.shape


# In[417]:


plt.imshow(image3, cmap = plt.cm.gray)


# In[418]:


image = np.fromfile("lighthouse3.raw", dtype = 'uint8')
image = image.reshape((256,256))
plt.imshow(image, cmap = plt.cm.gray)

l2 = rotateGeneral(image,-10-90)
plt.imshow(l2, cmap = plt.cm.gray)

vertices = []
x=0
for i in range(l2.shape[0]):
    if x==2:break
    for j in range(l2.shape[1]):
        if i-1 >= 0 and j-1 >= 0 and j+1 < l2.shape[1]:
#             print(image[i][j-1],image[i-1][j],image[i-1][j-1],image[i][j],(i,j))
            if l2[i][j-1]==255 and l2[i-1][j]==255 and l2[i-1][j-1]==255 and l2[i][j]!=255:
                x = i
                vertices.append((i,j))
            if i==x:
                if l2[i][j]==255 and l2[i+1][j]==255:
                    x=2
                    vertices.append((i,j-1))
                    break;

verticesback = []
x=0
for i in range(255,188,-1):
    if x==2:break
    for j in range(l2.shape[0]):
        if i+1 <= 255 and j+1 <= 255 and j-1 < l2.shape[1]:
#             print(image[i][j-1],image[i-1][j],image[i-1][j-1],image[i][j],(i,j))
            if l2[i][j+1]==255 and l2[i+1][j]==255 and l2[i+1][j+1]==255 and l2[i][j]!=255:
                x = i
                verticesback.append((i,j))
            if i==x:
                if l2[i][j]==255 and l2[i-140][j]==255:
                    x=2
                    verticesback.append((i,j-1))
                    break;

exact_edge = []
exact_edge.append(vertices[0])
exact_edge.append(vertices[-1])
exact_edge.append(verticesback[0])
exact_edge.append(verticesback[-1])

print(exact_edge)

plt.imshow(l2, cmap = plt.cm.gray)

print(np.sqrt(np.power((119-182),2) + np.power((221-78),2)))
print(np.sqrt(np.power((80-223),2) + np.power((183-115),2)))
centerx = (exact_edge[0][0] + exact_edge[3][0])//2
centery = (exact_edge[0][1] + exact_edge[3][1])//2

distx = abs(centerx - 128)
disty = abs(centery - 128)

print(distx,disty)

image2 = np.zeros(image.shape)
for i in range(image.shape[0]):
    for j in range(image.shape[1]):
        if(i>=exact_edge[0][0] and i+distx<256 and j+disty<256):
            image2[i-distx][j-disty] = l2[i][j]
            image2[i][j] = 255

plt.imshow(image2,cmap=plt.cm.gray)

num = exact_edge[0][1] - exact_edge[1][1]
den = 184 - 221
xr1 = int(128-abs(num/2))
xr2 = int(128+abs(num/2))
yr1 = int(128-abs(num/2))
yr2 = int(128+abs(num/2))
nim = image2[xr1:xr2,yr1:yr2]
plt.imshow(nim,cmap=plt.cm.gray)


# In[419]:


s = scale(nim,160/nim.shape[0])


# In[420]:


RightBottom = []
stop = 1
for i in range(315,350,1):
    if stop == 0: break
    for j in range(300,350,1):
        if target[i][j] == 255: 
            RightBottom.append((i,j))
            stop = 0
            break
print(RightBottom)


# In[421]:


for i in range(s.shape[0]):
    for j in range(s.shape[1]):
        t[i+RightBottom[0][0]][j+RightBottom[0][1]] = s[i][j]


# In[422]:


plt.imshow(t,cmap=plt.cm.gray)


# In[423]:


plt.imsave("FinalLightHouse.png",t,cmap=plt.cm.gray)


# In[ ]:




