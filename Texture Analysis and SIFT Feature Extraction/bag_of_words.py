import numpy as np
from matplotlib import pylab as plt
from sklearn.cluster import KMeans
from collections import defaultdict
import os
from os import walk


files = []
for (dirpath, dirnames, filenames) in walk(os.curdir):
     files.extend(filenames)
zeros_train_files = [] 
ones_train_files = [] 
for f in files:
    if 'zero' in f and 'raw' in f.split('.'):
        zeros_train_files.append(f)
    elif 'one' in f and 'raw' in f.split('.'):
        ones_train_files.append(f)


width = height = 28

zeros_train_images=[]
ones_train_images=[]

for file in zeros_train_files: 
    raw_image = open(file,'rb').read()
    raw_image = np.frombuffer(raw_image, np.uint8)
    zeros_train_images.append(np.reshape(raw_image, (width, height)))

for file in ones_train_files: 
    raw_image = open(file,'rb').read()
    raw_image = np.frombuffer(raw_image, np.uint8)
    ones_train_images.append(np.reshape(raw_image, (width, height)))


# defining sift feature extractor
sift = cv2.xfeatures2d.SIFT_create()

visual_dict = []
for img in zeros_train_images + ones_train_images:
    kp, des = sift.detectAndCompute(img,None)
    if des is not None:
        visual_dict.extend(des)

zero_hist  = defaultdict(int)
one_hist  = defaultdict(int)


kmeans = KMeans(n_clusters = 2, max_iter = 500).fit(visual_dict)


for img in zeros_train_images:
    kp, des = sift.detectAndCompute(img,None)
    if (des is not None):
        cluster_res =  kmeans.predict(des)
        for i in cluster_res:
            zero_hist[i] += 1.0        


for img in ones_train_images:
    kp, des = sift.detectAndCompute(img,None)
    if (des is not None):
        cluster_res =  kmeans.predict(des)
        for i in cluster_res:
            one_hist[i] += 1.0 


raw_image = open('eight.raw','rb').read()
raw_image = np.frombuffer(raw_image, np.uint8)
eight_image = np.reshape(raw_image, (width, height))

eight_hist = defaultdict(int)
kp, des = sift.detectAndCompute(eight_image,None)
if (des is not None):
    cluster_res =  kmeans.predict(des)
    for i in cluster_res:
        eight_hist[i] += 1.0 


plt.bar([0, 1], [one_hist[0], one_hist[1]])
plt.show()

plt.bar([0, 1], [zero_hist[0], zero_hist[1]])
plt.show()

plt.bar([0, 1], [eight_hist[0], eight_hist[1]])
plt.show()

#histogram intersection
zero_close = eight_hist[0]/zero_hist[0] + eight_hist[1]/zero_hist[1]
one_close = eight_hist[0]/one_hist[1] + eight_hist[1]/one_hist[1]


print("Intersection with zeros histogram:", zero_close)
print("Intersection with ones histogram:", one_close)

