# Geometric Modification and Morphological processing

This assignment focusses on implementing all possible geometric transformations utilizing them in different
applications. We also study various morphological processing techniques used for identifying, analyzing and modifying geometrical structures in an image by relying on non-linear operations related to shapes in an image.

## REQUIREMENTS

1. Ubuntu/Windows
2. C++ (g++ compiler)
3. Matlab 2016b+


## USAGE INFORMATION 

1. Geometrical Modification, run below command for 		each sub image (update the `file_name` variable 	with appropriate lighthouse sub-image names in 		file transform.py )
	```
	python transform.py
	```
	After runnning transform for all 3 sub images, then to get final filled image, run below command
	```
	python fillBoxes.py
	```

2. For Warping, run below command
	```
	python warping.py
	```
3. For Lens Distortion, run below command
	```
	python lens_distortion.py
	```
4. For Morphological Processing, use below commands 	for all the patterns, replacing pattern1 with 		appropriate next input pattern name
	```
	g++ shrinking.cpp
	./a.out pattern1.raw pattern1_s_out.raw 1 375 375

	g++ thinning.cpp
	./a.out pattern1.raw pattern1_thin_out.raw 1 375 375

	g++ skelotonizing.cpp
	./a.out pattern1.raw pattern1_skt_out.raw 1 375 375
	```
5. For defect detection, run below
	```
	g++ defectDetection.cpp
	./a.out deer.raw deer_out.raw 1 500 690
	```
6. For Rice grain Inspection, just run the file 		`rice_count.m` in matlab. It will give out 			histogram, shrinked image and grain count
