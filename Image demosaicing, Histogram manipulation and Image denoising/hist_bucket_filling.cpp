//Bucket filling based histogram manipulation

#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel = 1;
    int width = 400;
    int height = 400;

    // Check for proper syntax
    if (argc < 3){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
        return 0;
    }

    // Check if image is grayscale or color
    if (argc < 4){
        BytesPerPixel = 1; // default is grey image
    }
    else {
        BytesPerPixel = atoi(argv[3]);
        // Check if size is specified
        if (argc >= 5){
            width = atoi(argv[4]);
            height = atoi(argv[5]);
        }
    }

    // Allocate image data array
    unsigned char Imagedata[height][width][BytesPerPixel];

    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), width*height*BytesPerPixel, file);
    fclose(file);

    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

    unsigned char histImage[height][width];

    unsigned int bins = 256;
    unsigned int bin_size;

    //no of pixels per bucket
    bin_size = width*height/bins;

    //flatten image
    static vector<int> newimg;
    for (int i =0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            newimg.push_back((unsigned int)Imagedata[i][j][0]);
        }
    };

    std::sort(newimg.begin(),newimg.end());
//    //create bins
//    vector<int> vec[bin_size];
//
//    for (int k =0;k<bin_size;++k){
//
//        // get range for next set of n elements
//        auto start_itr = std::next(newimg.cbegin(), k*pixel_count);
//        auto end_itr = std::next(newimg.cbegin(), k*pixel_count + pixel_count);
//
//        // allocate memory for the sub-vector
//        vec[k].resize(pixel_count);
//
//        // code to handle the last sub-vector as it might
//        // contain less elements
//        if (k*pixel_count + pixel_count > newimg.size()) {
//            end_itr = newimg.cend();
//            vec[k].resize(newimg.size() - k*pixel_count);
//        }
//
//        // copy elements from the input range to the sub-vector
//        std::copy(start_itr, end_itr, vec[k].begin());
//
//    }

    int arr[256] = {};
    int index;

    //get equalized image
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            auto it = std::find(newimg.begin(), newimg.end(),(unsigned int)Imagedata[i][j][0]);
            if(it != newimg.end())
                index = std::distance(newimg.begin(), it);
                histImage[i][j] = (index + arr[(unsigned int)Imagedata[i][j][0]])/(bin_size);
                arr[(unsigned int)Imagedata[i][j][0]]++;
        }
    }


    // Write image data (filename specified by second argument) from ima ge data matrix

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(histImage, sizeof(unsigned char), width*height*BytesPerPixel, file);
    fclose(file);

    return 0;
}
