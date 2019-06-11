import numpy as np
from matplotlib import pylab as plt
from math import sin, cos, atan2, pi, ceil,floor

def read_image(file, height, width):
    raw_image = open(file,'rb').read()
    raw_image = np.frombuffer(raw_image, np.uint8)
    img = np.reshape(raw_image, (height,width))
    return img

def img_to_cart(x,y):
    return (x-255, 255-y)

def cart_to_img(x,y):
    return (x+255, 255-y)

def inverse_transform(xy_list, uv_list):
    X = np.zeros((6,6), int)
    for (x,y),i in zip(xy_list,range(len(X))):
        X[i] = np.array([1,x,y,x**2,x*y,y**2])
    
    Xinv = np.linalg.inv(X)
    
    U = np.zeros((6,2), int)
    for (u,v),i in zip(uv_list,range(len(U))):
        U[i] = np.array([u,v])
    
    a = np.matmul(Xinv, U.T[0])
    b = np.matmul(Xinv, U.T[1])
    
    out_matrix = np.vstack((a,b))
    return out_matrix

def interpolate(i,j,img):
    y = floor(i)
    x = floor(j)
    a,b = j - x, i - y
    return int((1-a)*((1-b)*img[x][y]+b*img[x+1][y]) + a*((1-b)*img[x][y+1]+b*img[x+1][y+1]))

#read image
height=width=512
filename ='hat.raw'
img = read_image(filename,height,width)

# define control points
x1 = y1 = y2 = x3 = y5 = x6 = 0
x2 = x4 = x7 = width-1
y3 = y4 = y8 = height-1
xc = x5 = x8 = (width-1)//2
yc = y7 = y6 = (height-1)//2
x1c,y1c = (x1+xc)//2, (y1+yc)//2
x2c,y2c = (x2+xc)//2, (y2+yc)//2
x3c,y3c = (x3+xc)//2, (y3+yc)//2
x4c,y4c = (x4+xc)//2, (y4+yc)//2

print("Input u-v coordinates:")
top_uv_coordinates = [(x1,y1),(x1c,y1c),(xc,yc),(x2c,y2c),(x2,y2),(x5,y5)]
#print(top_uv_coordinates)
left_uv_coordinates = [(x1,y1),(x1c,y1c),(xc,yc),(x3c,y3c),(x3,y3),(x6,y6)]
#print(left_uv_coordinates)
right_uv_coordinates = [(x2,y2),(x2c,y2c),(xc,yc),(x4c,y4c),(x4,y4),(x7,y7)]
#print(right_uv_coordinates)
bottom_uv_coordinates = [(x3,y3),(x3c,y3c),(xc,yc),(x4c,y4c),(x4,y4),(x8,y8)]
#print(bottom_uv_coordinates)

print("Output x-y coordinates:")
arc_height = arc_width = 128
top_xy_coordinates = [(x1,y1),(x1c,y1c),(xc,yc),(x2c,y2c),(x2,y2),(x5,arc_height)]
#print(top_xy_coordinates)
left_xy_coordinates = [(x1,y1),(x1c,y1c),(xc,yc),(x3c,y3c),(x3,y3),(arc_width,y6)]
#print(left_xy_coordinates)
right_xy_coordinates = [(x2,y2),(x2c,y2c),(xc,yc),(x4c,y4c),(x4,y4),(width-arc_width,y7)]
#print(right_xy_coordinates)
bottom_xy_coordinates = [(x3,y3),(x3c,y3c),(xc,yc),(x4c,y4c),(x4,y4),(x8,height-arc_height)]
#print(bottom_xy_coordinates)

#get top matrix
xy_list = [img_to_cart(x,y) for (x,y) in top_xy_coordinates]
uv_list = [img_to_cart(u,v) for (u,v) in top_uv_coordinates]
top_matrix = inverse_transform(xy_list, uv_list)

xy_list = [img_to_cart(x,y) for (x,y) in left_xy_coordinates]
uv_list = [img_to_cart(u,v) for (u,v) in left_uv_coordinates]
left_matrix = inverse_transform(xy_list, uv_list)

xy_list = [img_to_cart(x,y) for (x,y) in bottom_xy_coordinates]
uv_list = [img_to_cart(u,v) for (u,v) in bottom_uv_coordinates]
bottom_matrix = inverse_transform(xy_list, uv_list)

xy_list = [img_to_cart(x,y) for (x,y) in right_xy_coordinates]
uv_list = [img_to_cart(u,v) for (u,v) in right_uv_coordinates]
right_matrix = inverse_transform(xy_list, uv_list)

warped_img = np.zeros((512,512))
for i in range(512//2):
    for j in range(i,512-i):
        x,y = j-255,255 - i
        u,v = np.matmul(top_matrix,[1,x,y,x**2,x*y,y**2])
        p,q = u + 255,255 - v        
        if 1<=p<=511 and 1<=q<=511:
            val = interpolate(p,q,img)
            warped_img[i][j] = val

for i in range(512//2):
    for j in range(i,512-i):
        x,y = i-255, 255-j
        u,v = np.matmul(left_matrix,[1,x,y,x**2,x*y,y**2])
        p,q = u + 255, 255 - v
        if 0<=p<=511 and 0<=q<=511:
            val = interpolate(p,q,img)
            warped_img[j][i] = val

for i in range(511,255,-1):
    for j in range(511-i,i+1):
        x,y = j-255, 255 - i 
        u,v = np.matmul(bottom_matrix,[1,x,y,x**2,x*y,y**2])
        p,q = u + 255,255-v
        if 0<=p<511 and 0<=q<511:
            val = interpolate(p,q,img)
            warped_img[i][j] = val

for i in range(511,255,-1):
    for j in range(511-i,i+1):
        x,y = i-255, 255-j
        u,v = np.matmul(right_matrix,[1,x,y,x**2,x*y,y**2])
        p,q = u + 255,255 - v
        if 0<=p<=511 and 0<=q<=511:
            val = interpolate(p,q,img)
            warped_img[j][i] = val

#write image to file
warped_img.astype('int8').tofile('warped_'+filename)                                                