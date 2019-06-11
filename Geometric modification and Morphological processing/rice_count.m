close all;
clc;

img_size = 690*500*3;
f = fopen('rice.raw','r');
raw_img = fread(f,img_size, 'uint8=>uint8');

k=1;
for i=1:3:(img_size)-2
    R(k)=raw_img(i);
    k=k+1;
end

k=1;
for i=2:3:(img_size)-1
    G(k)=raw_img(i);
    k=k+1;
end

k=1;
for i=3:3:(img_size)
    B(k)=raw_img(i);
    k=k+1;
end

r = reshape(R,690,500)';
g = reshape(G,690,500)';
b = reshape(B,690,500)';

img = cat(3,r,g,b);

IG = rgb2gray(img);

%binarize image
BW = edge(IG, 'canny', 0.09);

%dilate image
SED = strel('diamond',2);
BWdilate = imdilate(BW,SED);

%fill holes
BWfill = imfill(BWdilate,'holes');

%erode image
SEO = strel('octagon',3);
BWerode = imerode(BWfill, SEO);

%additonal mask to handle loose connectivity
BWM = bwhitmiss(BWerode,[1 0 1;0 1 0;1 0 1]);

%shrink image
BWshrink = bwmorph(BWM,'shrink','inf');
% figure;
% imshow(BWshrink)

%count number of holes
grain_count = 0;
for i = 1:500
    for j = 1:690
        if BWshrink(i,j)== 1
            grain_count=grain_count + 1;
        end
    end
end

%connected component labelling
L = bwlabel(BWM);
grain_data = regionprops(L, {'Area'});
grain_areas = [grain_data.Area];
sorted_grain = sortrows(struct2table(grain_data));
histogram(grain_areas)
title('Histogram of Rice Grain Area')