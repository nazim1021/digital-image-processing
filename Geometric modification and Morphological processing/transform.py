import numpy as np
from matplotlib import pylab as plt
from math import sin, cos, atan2, pi, ceil,sqrt, floor

def read_image(file, height, width):
    raw_image = open(file,'rb').read()
    raw_image = np.frombuffer(raw_image, np.uint8)
    img = np.reshape(raw_image, (height,width))
    return img

def img_to_cart(x,y):
    #return (x, 255-y)
    return (x-128, 128-y)

def cart_to_img(x,y):
    #return (x, 255-y)
    return (x+128, 128-y)

def interpolate(i,j,img):
    y = floor(i)
    x = floor(j)
    a,b = j - x, i - y
    return int((1-a)*((1-b)*img[x][y]+b*img[x+1][y]) + a*((1-b)*img[x][y+1]+b*img[x+1][y+1]))

def scale_image(img, height, width, fx,fy):
    scaled_img = np.empty((height,width), np.uint8)
    for i in range(height):
        for j in range(width):
            x,y = i/fx,j/fy
            if (0<=x<img.shape[0]-1 and 0<=y<img.shape[1]-1):
                pixel = interpolate(y,x,img)
                scaled_img[i][j] = pixel
            else:
                scaled_img[i][j] = 255
    return scaled_img    

filename='lighthouse3.raw'
img = read_image(filename,256, 256)
plt.imshow(img, cmap= 'gray')
plt.show() 

x1 = y1 = x2 = y2 = 0

# find top and bottom corners
for i in range(256):
    for j in range(256):
        if img[i][j]!=255:
            if x2==0 and y2 ==0:
                x2,y2 = j,i
            else:
                x4,y4 = j,i
            continue

# find left and right corners
for i in range(256):
    for j in range(256):
        if img[j][i]!=255:
            if x1==0 and y1==0:
                x1,y1 =  i,j
            else:
                x3,y3 = i,j
            continue

x_c = (x2+x4)/2
y_c = (y2+y4)/2

cx = round(255/2)
cy = round(255/2)

#get translation offset
tx = x_c 
ty = y_c

coordinates = [(x1,y1), (x2,y2), (x3,y3),(x4,y4), (cx,cy), (x_c,y_c),(tx,ty)]
cart_coordinates = [img_to_cart(x,y) for x,y in coordinates]


#get rotation angle
#theta = atan2((cart_coordinates[3][1]-cart_coordinates[2][1]),(cart_coordinates[3][0]-cart_coordinates[2][0])) # lighthouse 1
#theta = atan2((cart_coordinates[2][1]-cart_coordinates[1][1]),(cart_coordinates[2][0]-cart_coordinates[1][0])) # lighthouse 2
theta = atan2((cart_coordinates[1][1]-cart_coordinates[0][1]),(cart_coordinates[1][0]-cart_coordinates[0][0])) # lighthouse 3

cart_tx = cart_coordinates[6][0]
cart_ty = cart_coordinates[6][1]

#theta =  pi/2 - theta # lighthouse 3
#theta = pi-theta # Lighthouse 2
theta = pi - theta # lighthouse 1
transformed_img = np.empty((256,256), np.uint8)
for j in range(256):
    for k in range(256):
        p,q = img_to_cart(k,j)
        #translate
        a,b = p-cart_tx,q-cart_ty
        # rotate
        u,v = (a*cos(theta) + b*sin(theta)) , (-a*sin(theta) + b*cos(theta))        
        #translate
        a,b = u+cart_tx,v+cart_ty
        x,y  =  cart_to_img(a,b)
        
        if (0<=x<=255 and 0<=y<=255):
            val = interpolate(x,y,img)
            transformed_img[j][k] = img[round(y)][round(x)]
        else:
            transformed_img[j][k] = 255

plt.imshow(transformed_img,cmap='gray') 
transformed_img.astype('int8').tofile('transformed_'+filename)
plt.show()

flag= True
for y in range(256):
    for x in range(256):
        if transformed_img[x][y]!=255 and flag:
            new_y1,new_x1 = y,x
            flag = False
            continue
        elif transformed_img[x][y] !=255 and y == new_y1:
            new_y2 = y
            new_x2 = x
            if x>new_x2:
                new_x2 = x
            continue

for i in range(256):
    for j in range(256):
        if transformed_img[j][i]!=255 and j==new_x1 and i>new_y1:
            new_y3,new_x3 = i,j
            continue
        elif transformed_img[j][i]!=255 and i == new_y3:
            new_y4 = i
            new_x4 = j
            if j > new_x4:
                new_x4 = j
            continue

# print(new_x1," ",new_y1,"\n")
# print(new_x2," ",new_y2,"\n")
# print(new_x3," ",new_y3,"\n")
# print(new_x4," ",new_y4,"\n")

final_img = transformed_img[new_y1:new_y4+1, new_x1:new_x4+1]
height=width=160
fx = width/final_img.shape[0]
fy = height/final_img.shape[1]
scaled_img = scale_image(final_img, height,width, fx,fy)
scaled_img.astype('int8').tofile('new_'+filename)

