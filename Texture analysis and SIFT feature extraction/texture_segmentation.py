# Texture Segmentation

import numpy as np
import cv2
from matplotlib import pyplot as plt
from sklearn.decomposition import PCA
from mpl_toolkits.mplot3d import Axes3D
from sklearn.cluster import KMeans


width = height = 510
raw_image = open('comb.raw','rb').read()
raw_image = np.frombuffer(raw_image, np.uint8)
comb_img = np.reshape(raw_image, (height, width))


#preprocessing
normalized_comb_img = comb_img - np.mean(comb_img)
padded_img = np.pad(normalized_comb_img, 2,'reflect')


#filter convolution
def convolve(i,j,filter,img):
    val = 0.0
    for m in range(-2,3):
        for n in range(-2,3):
            val += img[i+m][j+n]*filter[m+2][n+2]
    return val


#Laws Filters
L5 = np.array([1,4,6,4,1]).reshape(5,1)
E5 = np.array([-1,-2,0,2,1]).reshape(5,1)
S5 = np.array([-1,0,2,0,-1]).reshape(5,1)
R5 = np.array([-1,2,0,-2,1]).reshape(5,1)
W5 = np.array([1,-4,6,-4,1]).reshape(5,1)

laws_filters = {'L5':L5,'E5':E5,'S5':S5,'R5':R5,'W5':W5}

_2d_laws_filters = []
for k1,v1 in laws_filters.items():
    for k2,v2 in laws_filters.items():
        _2d_laws_filters.append(np.matmul(v1,v2.T))


#Laws feature extraction
filtered_images=[]
for filt in _2d_laws_filters:
    filtered_img = np.zeros((510,510))
    for i in range(2,512):
        for j in range(2,512):
            filtered_img[i-2][j-2] = convolve(i,j,filt,padded_img)
    
    filtered_images.append(filtered_img)




#Boudary extension for applying windows
win_size = 21
extended_filtered_images=[]
for img in filtered_images:
    extended_filtered_images.append(np.pad(img,win_size//2,'reflect'))

extended_filtered_images = np.array(extended_filtered_images)



#Energy feature computation
energy_vectors=[]
for i in range(510):
    for j in range(510):
        features=[]
        for img in extended_filtered_images:
            features.append(np.sum(np.abs(img[i:i+win_size,j:j+win_size]))/win_size**2)
        energy_vectors.append(np.array(features))



#Energy feature normalization
energy_vectors = np.array(energy_vectors)
normalized_features = (energy_vectors - np.mean(energy_vectors,axis=0))/np.std(energy_vectors,axis=0)
normalized_features = normalized_features[:,1:]



#pca computation
# pca = PCA(n_components = 3)
# reduced_features = pca.fit_transform(normalized_features)


#clustering
kmeans = KMeans(n_clusters = 7).fit(reduced_features)
labels = kmeans.labels_.reshape(510,510)



final_image = np.empty((height, width), np.uint8)

for i in range(height):
    for j in range(width):
        if labels[i][j]==0:
            final_image[i][j] = 0
        elif labels[i][j]==1:
            final_image[i][j] = 42
        elif labels[i][j]==2:
            final_image[i][j] = 85
        elif labels[i][j]==3:
            final_image[i][j] = 126
        elif labels[i][j]==4:
            final_image[i][j] = 168
        elif labels[i][j]==5:
            final_image[i][j] = 210
        else:
            final_image[i][j] = 255
            
plt.imshow(final_image, cmap='gray')
plt.show()


#hole closing
closed_image = cv2.morphologyEx(final_image, cv2.MORPH_CLOSE, np.ones((7,7), np.float32))
plt.imshow(closed_image, cmap='gray')
plt.show()

