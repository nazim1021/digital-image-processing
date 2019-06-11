# Edge Detection and Digital Halftoning

Edge detection, is a process of identifying object edges in an image. In this assignment, we will work on understanding commonly used edge detection methods. Additionally, we also implement various approaches to Digital halftoning - it is a process of representing original digital image with black and white pixels only

## Requirements

1. Ubuntu/Windows
2. C++ (g++ compiler)
3. Matlab 2016b+ 

## USAGE INFORMATION

Use below commands to run respective files
```
g++ constant_threshold.cpp -o constant
./constant bridge.raw bridge_constant.raw 1 600 400

g++ random_thresholding.cpp -o random
./random bridge.raw bridge_random.raw 1 600 400

g++ dithering.cpp -o dithering
./dithering bridge.raw bridge_dither_out.raw 1 600 400

g++ error_diffusion.cpp -o fs 
./fs bridge.raw bridge_fs.raw 1 600 400

g++ error_diffusion_jjn.cpp -o jjn 
./jjn bridge.raw bridge_jjn.raw 1 600 400

g++ error_diffusion_stucki.cpp -o stucki
./stucki bridge.raw bridge_stucki.raw 1 600 400

g++ separable.cpp -o separable
./separable bird.raw bird_sep.raw 3 500 375

g++ mbvq.cpp -o mbvq
./mbvq bird.raw bird_out.raw 3 500 375
```
For Canny edge detection, run the file `canny.m`
For performance evaluation use file `cannyEdgeEval.m`
```
g++ sobel.cpp -o sobel
./sobel pig.raw pig_out.raw 3 481 321
g++ sobel.cpp -o sobel
./sobel tiger.raw tiger_out.raw 3 481 321
```
For Structured Edge detection and evaluation
run `edgesDemo.m` and for performance evaluation - supporting files included are `evalEdge.m` and `edgesEvalImgNew.m`
