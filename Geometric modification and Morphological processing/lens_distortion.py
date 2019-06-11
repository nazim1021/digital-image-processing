# EE569 Assignment 3 - Problem 1 (c)
# Name: Nazim Shaikh
# USC ID: 8711456229
# USC EMAIL: nshaikh@usc.edu
# Submission Date: 03/03/2019

import numpy as np
from matplotlib import pylab as plt
from math import sin, cos, atan2, pi, ceil,sqrt, floor

def read_image(file, height, width):
    raw_image = open(file,'rb').read()
    raw_image = np.frombuffer(raw_image, np.uint8)
    img = np.reshape(raw_image, (height,width))
    return img

def img_to_cam(u,v, uc,vc,fx,fy):
    return (u-uc)/fx, (v-vc)/fy

def cam_to_img(x,y, uc,vc,fx,fy):
    return (x*fx+uc), (y*fy+vc)

def distortion_fuction(k1,k2,x,y):
    r2 = x**2 + y**2
    r4 = r2**2
    r6 = r4**2
    c = (1+k1*r2+k2*r4)
    return x*c,y*c

def interpolate(i,j,img):
    y = floor(i)
    x = floor(j)
    a,b = j - x, i - y
    return int((1-a)*((1-b)*img[x][y]+b*img[x+1][y]) + a*((1-b)*img[x][y+1]+b*img[x+1][y+1]))

filename = 'classroom.raw'
height = 712; width= 1072
img = read_image(filename,height,width)

#img = np.pad(img, (100,100), 'constant', constant_values = (0,0))
#height=img.shape[0];width=img.shape[1]
uc,vc = width/2, height/2
fx=fy=600; k1 = -0.3536; k2= 0.1730;k3 =0

final_img = np.zeros((height, width))

for i in range(height):
    for j in range(width):
        x,y = img_to_cam(j,i, uc,vc,fx,fy)
        xd,yd = distortion_fuction(k1,k2,x,y)
        u,v = cam_to_img(xd,yd, uc,vc,fx,fy)
        if 0<=u<width and 0<=v<height:
            val = interpolate(u,v,img)
            final_img[i][j] = val
        else:
            final_img[i][j] = 255
            
#write image to file
final_img.astype('int8').tofile('undistorted_'+filename)
