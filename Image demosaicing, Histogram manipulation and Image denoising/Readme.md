# Image demosaicing, Histogram manipulation and Image denoising

Image demosaicing is a process of converting grayscale/raw images into full color images while Histogram manipulation helps in adjusting contrast of grayscale using its histogram. In first part of the assignment, we focus on implementing Image demosaicing and histogram manipulation techniques to gray scale images.

Image Denoising is the process of removing noise from image. It is an important preprocessing step for further image analysis. Different types of noise that can corrupt image are Gaussian noise, uniform noise, impulse noise, etc. To deal with each of them we have different filters. In this 2nd part,  we try to implement Linear filters, Bilateral filter, non-local mean filters etc. on grayscale as well as color images and observe the performance with each of them.

## Requirements

1. Ubuntu/Windows
2. Vscode
3. C++ (g++ compiler)

## USAGE INFORMATION

Use below syntax to run respective files:
```
g++ filename.cpp
./filename inputImageName outputImageName BytesPerPixel Width Height
```
Example:
```
g++ bilinear.cpp
./bilinear cat.raw cat_bilinear_out.raw 1 390 300
```