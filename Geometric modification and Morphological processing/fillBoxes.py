import numpy as np
from math import sin, cos, atan2, pi, ceil
from matplotlib import pylab as plt

def read_image(file, height, width):
    """
    function to read raw images
    """
    raw_image = open(file,'rb').read()
    raw_image = np.frombuffer(raw_image, np.uint8)
    img = np.reshape(raw_image, (height,width))
    return img

#functions to detect corners for extracting white boxes
def is_bottom_left_corner(img, x,y):
    return (img[y][x] == 255 and img[y][x-1]<255 and img[y][x+1]==255 and img[y+1][x]<255 and img[y-1][x]== 255)

def is_top_left_corner(img, x,y):
    return (img[y][x] == 255 and img[y][x-1]<255 and img[y][x+1]==255 and img[y+1][x]==255 and img[y-1][x]<255)

def is_top_right_corner(img, x,y):
    return (img[y][x] == 255 and img[y][x-1]==255 and img[y][x+1]<255 and img[y+1][x]==255 and img[y-1][x]<255)

def is_bottom_right_corner(img, x,y):
    return (img[y][x] == 255 and img[y][x-1]==255 and img[y][x+1]<255 and img[y+1][x]<255 and img[y-1][x]==255)

def getSubImageCoordinates(img):
    """
    function to obtain coordinates of all white boxes
    """
    x1 = y1 = x3 = y3 = x4 = y4 = x5 = y5= 0 
    x6 = y6 = x7 = y7 = x8 = y8 = 0
    x9 = y9 = x10 = y10 = x11 = y11 = 0
    x12 = y12 = 0

    for y in range(512):
        for x in range(512):
            if img[y][x]==255 and x1==0 and y1 ==0:
                y1,x1= y,x
                continue
            elif y == y1 and is_top_right_corner(img, x,y):
                y2 = y
                x2 = x
                if x>x2:
                    x2 = x
                continue
            elif is_bottom_left_corner(img, x,y) and x == x1:
                y3,x3 = y,x
                continue
            elif y == y3 and is_bottom_right_corner(img, x,y):
                    y4 = y
                    x4 = x
                    if x>x4:
                        x4 = x
                    continue
            elif x < x1 and is_top_left_corner(img, x,y):
                y5,x5= y,x
                continue
            elif y == y5 and is_top_right_corner(img, x,y):
                y6 = y
                x6 = x
                if x > x6:
                    x6 = x
                continue
            elif is_bottom_left_corner(img, x,y) and x == x5:
                y7,x7 = y,x
                continue
            elif y == y7 and is_bottom_right_corner(img, x,y):
                y8 = y
                x8 = x
                if x>x8:
                    x8 = x
                continue
            elif x > x8 and y > x8 and is_top_left_corner(img, x,y):
                y9,x9= y,x
                continue
            elif y == y9 and is_top_right_corner(img, x,y):
                y10 = y
                x10 = x
                if x > x10:
                    x10 = x
                continue
            elif is_bottom_left_corner(img, x,y) and x == x9:
                y11,x11 = y,x
                continue
            elif y == y11 and is_bottom_right_corner(img, x,y):
                y12 = y
                x12 = x
                if x>x12:
                    x12 = x
                continue   
    return [(x1,y1),(x2,y2),(x3,y3),(x4,y4),(x5,y5),(x6,y6),(x7,y7),(x8,y8),(x9,y9),(x10,y10),(x11,y11),(x12,y12)]


lighthouse = read_image('lighthouse.raw', 512,512)

new_lighthouse = np.copy(lighthouse)
pos = getSubImageCoordinates(lighthouse)


lighthouse1 = read_image('new_lighthouse1.raw', 160,160)
lighthouse2 = read_image('new_lighthouse2.raw', 160,160)
lighthouse3 = read_image('new_lighthouse3.raw', 160,160)
new_lighthouse[pos[0][1]:pos[3][1]+1, pos[0][0]:pos[3][0]+1] = lighthouse2
new_lighthouse[pos[4][1]:pos[7][1]+1, pos[4][0]:pos[7][0]+1] = lighthouse1
new_lighthouse[pos[8][1]:pos[11][1]+1, pos[8][0]:pos[11][0]+1] = lighthouse3

#write final image to file
new_lighthouse.astype('int8').tofile('filled_lighthouse.raw')
