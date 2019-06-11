# Texture Classification

import numpy as np
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import pylab as plt
import os, cv2
from sklearn.cluster import KMeans
from sklearn.decomposition import PCA

files = []
for (dirpath, dirnames, filenames) in os.walk(os.curdir):
    files.extend(filenames)
    
texture_files = []    
for f in files:
    if 'texture' in f and 'raw' in f.split('.'):
        texture_files.append(f)


width = height = 128

texture_images=[]
for file in texture_files:
    raw_image = open(file,'rb').read()
    raw_image = np.frombuffer(raw_image, np.uint8)
    img = np.reshape(raw_image, (height, width))
    texture_images.append(img)


#pre-processing
normazlized_texture_images  = []
for img in texture_images:
    new_img = img - np.mean(img)
    normazlized_texture_images.append(new_img)

#Laws Filter creation
L5 = np.array([1,4,6,4,1]).reshape(5,1)
E5 = np.array([-1,-2,0,2,1]).reshape(5,1)
S5 = np.array([-1,0,2,0,-1]).reshape(5,1)
R5 = np.array([-1,2,0,-2,1]).reshape(5,1)
W5 = np.array([1,-4,6,-4,1]).reshape(5,1)

laws_filters = {'L5':L5,'E5':E5,'S5':S5,'R5':R5,'W5':W5}

_2d_laws_filters = {}
for k1,v1 in laws_filters.items():
    for k2,v2 in laws_filters.items():
        _2d_laws_filters[k1+k2] = np.matmul(v1,v2.T)


#boundary extension by pixel replication
extended_images  = []
for img in normazlized_texture_images:
    new_img = np.pad(img, 2,'reflect')
    extended_images.append(new_img)    



#filter convolution
def convolve(i,j,filt,img):
    val = 0
    for m in range(-2,3):
        for n in range(-2,3):
            val += img[i+m][j+n]*filt[m+2][n+2]
    return val


#Laws feature extraction
final_images = []
for img in extended_images:
    filtered_images = []
    for filt, val in _2d_laws_filters.items():
        new_img = np.empty((height,width), np.uint8)
        for i in range(2,height+2):
            for j in range(2,width+2):
                new_img[i-2][j-2] = convolve(i,j,val,img) 
        filtered_images.append(new_img)                   
    final_images.append(filtered_images)


#Energy feature computation
features= []
for images in final_images:
    energy_vector = []
    for img in images:
        energy_vector.append(np.sum(np.abs(img))/(height*width))
    features.append(energy_vector)
features_arr = np.array(features)


#Energy feature normalization
normalized_features = []
for feature in features_arr:
    feature =  (feature - np.mean(feature))/(np.std(feature))
    normalized_features.append(feature)
normalized_features = np.array(normalized_features)


#excluding non zero mean L5L5 filter 
normalized_features = normalized_features[:,1:] 

#pca computation
pca = PCA(n_components=3)
reduced_features = pca.fit_transform(normalized_features)


fig = plt.figure(1, figsize=(10, 8))
ax = plt.axes(projection='3d')
ax.scatter3D(reduced_features[:,0], reduced_features[:,1], reduced_features[:,2], color=['r','g','b','c','g','b','c','r','c','r','g','b'])

#clustering
kmeans = KMeans(n_clusters=4, max_iter = 500).fit(reduced_features)
labels = kmeans.labels_


print('Class 0:')
for k in range(12):
    if labels[k]==0:
        plt.imshow(texture_images[k],cmap='gray')
        plt.show()
        
print('Class 1:')
for k in range(12):
    if labels[k]==1:
        plt.imshow(texture_images[k],cmap='gray')
        plt.show()
        
print('Class 2:')
for k in range(12):
    if labels[k]==2:
        plt.imshow(texture_images[k],cmap='gray')
        plt.show()
        
print('Class 3:')
for k in range(12):
    if labels[k]==3:
        plt.imshow(texture_images[k],cmap='gray')
        plt.show()

#variance calculation for feature discriminant analysis
max_discriminant_feature = np.argmax([np.var(features_arr[:, i]) for i in range(25)])
min_discriminant_feature = np.argmin([np.var(features_arr[:, i]) for i in range(25)])

#feature plot for feature discriminant analysis
# for i in range(0,25):
#     plt.bar(features_arr[:,i],[1]*12, width=0.01, color=['r','g','b','c','g','b','c','r','c','r','g','b'])
#     plt.show()
#     plt.title('Feature '+str(i+1))
#     plt.xlabel('Feature Values')
#     plt.ylabel('Count')