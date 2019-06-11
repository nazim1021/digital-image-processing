//Name: Nazim Shaikh
//USC ID: 8711456229
//USC EMAIL: nshaikh@usc.edu
//Submission Date: 01/22/2019


//Below code implements linear uniform filtering for image denoising

#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>

using namespace std;

//// Utility function to print a vector
//template<typename T>
//void print(std::vector<T> const &v)
//{
//    for (auto &i: v)
//        std::cout << i << ' ';
//
//    std::cout << '\n';
//}

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

    unsigned char extendedImage[height+2][width+2];

    //extend columns
    for (int i = 0; i < height; i++)
    {
        extendedImage[i+1][0] = Imagedata[i][1][0];
        extendedImage[i+1][width+1] = Imagedata[i][width-2][0];
    }

    //extend rows
    for (int j = 0; j < width; j++) {
        extendedImage[0][j+1] = Imagedata[1][j][0];
        extendedImage[height+1][j+1] = Imagedata[height-2][j][0];
    }

    //get extended image
    for (int i = 0; i < height; i++) {
        for (int j =0 ; j < width; j++){
            extendedImage[i+1][j+1] = Imagedata[i][j][0];
        }
    }

    unsigned char denoiseImage[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            denoiseImage[i][j] = (extendedImage[i][j] + extendedImage[i][j+1] + extendedImage[i][j+2]+
            extendedImage[i+1][j]+extendedImage[i+1][j+1]+ extendedImage[i+1][j+2]+
            extendedImage[i+2][j]+extendedImage[i+2][j+1]+ extendedImage[i+2][j+2])/9;
        };
    };

    // Write image data (filename specified by second argument) from ima ge data matrix

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(denoiseImage, sizeof(unsigned char), width*height*BytesPerPixel, file);
    fclose(file);

    return 0;
}
