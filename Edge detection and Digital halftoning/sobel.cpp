//Name: Nazim Shaikh
//USC ID: 8711456229
//USC EMAIL: nshaikh@usc.edu
//Submission Date: 02/12/2019

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <map>

using namespace std;

int main(int argc, char *argv[])
{
    FILE *imagefile;
    int BytesPerPixel = 1;
    int width = 400;
    int height = 600;

    // Check for proper syntax
    if (argc < 3)
    {
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
        return 0;
    }

    // Check if image is grayscale or color
    if (argc < 4)
    {
        BytesPerPixel = 1; // default is grey image
    }
    else
    {
        BytesPerPixel = atoi(argv[3]);
        // Check if size is specified
        if (argc >= 5)
        {
            width = atoi(argv[4]);
            height = atoi(argv[5]);
        }
    }

    // Allocate image data array
    unsigned char Imagedata[height][width][BytesPerPixel];

    // Read image (filename specified by first argument) into image data matrix
    if (!(imagefile = fopen(argv[1], "rb")))
    {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), width * height * BytesPerPixel, imagefile);
    fclose(imagefile);

    unsigned char extendedImage[height + 2][width + 2][BytesPerPixel];

    //get extended image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            extendedImage[i + 1][j + 1][0] = Imagedata[i][j][0];
            extendedImage[i + 1][j + 1][1] = Imagedata[i][j][1];
            extendedImage[i + 1][j + 1][2] = Imagedata[i][j][2];
        }
    }

    //extend rows
    for (int j = 0; j < width; j++)
    {
        extendedImage[0][j + 1][0] = Imagedata[1][j][0];
        extendedImage[0][j + 1][1] = Imagedata[1][j][1];
        extendedImage[0][j + 1][2] = Imagedata[1][j][2];

        extendedImage[height + 1][j + 1][0] = Imagedata[height - 2][j][0];
        extendedImage[height + 1][j + 1][1] = Imagedata[height - 2][j][1];
        extendedImage[height + 1][j + 1][2] = Imagedata[height - 2][j][2];
    }

    //extend columns
    for (int i = 0; i < height + 2; i++)
    {
        extendedImage[i + 1][0][0] = extendedImage[i][1][0];
        extendedImage[i + 1][0][1] = extendedImage[i][1][1];
        extendedImage[i + 1][0][2] = extendedImage[i][1][2];

        extendedImage[i + 1][width + 1][0] = extendedImage[i][width - 2][0];
        extendedImage[i + 1][width + 1][1] = extendedImage[i][width - 2][1];
        extendedImage[i + 1][width + 1][2] = extendedImage[i][width - 2][2];
    }

    //convert to gray scale
    unsigned char grayImage[height+2][width+2];
    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            unsigned int R = extendedImage[i][j][0];
            unsigned int G = extendedImage[i][j][1];
            unsigned int B = extendedImage[i][j][2];

            float gray = ceil(0.3*R + 0.59*G + 0.11*B);

            grayImage[i][j]  = gray;
        }
    }


    float xGradient[height][width];
    float yGradient[height][width];

    unsigned char xGrad[height][width];
    unsigned char yGrad[height][width];
    unsigned int gradMag[height][width];

    unsigned char edgedImage[height][width];

    float T = 0.8;

    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            int x_pixel  = -2*grayImage[i][j-1]+2*grayImage[i][j+1]-grayImage[i-1][j-1]
                                    + grayImage[i-1][j+1] - grayImage[i+1][j-1] + grayImage[i+1][j+1];
            xGradient[i-1][j-1] = x_pixel;

            int y_pixel  = grayImage[i-1][j-1]+ 2*grayImage[i-1][j] + grayImage[i-1][j+1] 
                            -grayImage[i+1][j-1] -2*grayImage[i+1][j] - grayImage[i+1][j+1];
            
            yGradient[i-1][j-1] = y_pixel;
            gradMag[i-1][j-1] = (unsigned int)(sqrt((x_pixel * x_pixel) + (y_pixel * y_pixel)));
            //edgedImage[i-1][j-1] = (sqrt((x_pixel * x_pixel) + (y_pixel * y_pixel))/255.0) > T ? 0: 255;
        }
    }        

    float y_max = yGradient[0][0]; 
    float x_max = xGradient[0][0];
    float y_min = yGradient[0][0];
    float x_min = xGradient[0][0];
    int grad_max = gradMag[0][0];
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width ; j++)
        {
             if(xGradient[i][j]>x_max){
                 x_max = xGradient[i][j];
             }
             if(xGradient[i][j]<x_min){
                 x_min = xGradient[i][j];
             }
             if(yGradient[i][j] < y_min){
                 y_min = yGradient[i][j];
             }
             if(yGradient[i][j] > y_max){
                 y_max = yGradient[i][j];
             }
             if(gradMag[i][j] > y_max){
                 grad_max = gradMag[i][j];
             }
        }
    };

    float x_range = x_max - x_min;
    float y_range = y_max - y_min;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            xGradient[i][j] = ((xGradient[i][j] - x_min)/(x_range))*255.0;
            yGradient[i][j] = ((yGradient[i][j] - y_min)/(y_range))*255.0;
            xGrad[i][j] = (unsigned char)xGradient[i][j];
            yGrad[i][j] = (unsigned char)yGradient[i][j];
        }
    }

    std::map<int, float> histmap;
    for (int k = 0; k < grad_max; k++) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (k == (unsigned int) gradMag[i][j]) {
                    histmap[k] = histmap[k] + 1;
                }
            }
        }
    }

    for (int k=0;k<grad_max;k++) {
        histmap[k] = histmap[k]/(height*width);
    }   
    
    //get cdf
    for (int k =1;k<grad_max;k++){
        histmap[k]=histmap[k]+histmap[k-1];
    }

    int grad_mag = 0;
     //get equalized image
    for (int k = 0; k<grad_max; k++) {
        if (histmap[k]>=T){
            grad_mag = k;
            break;
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            edgedImage[i][j] = (gradMag[i][j] > grad_mag) ? 0: 255;
        }
    } 

    // Write edge map  data (filename specified by second argument) from image data matrix
    if (!(imagefile = fopen(argv[2], "wb")))
    {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(edgedImage, sizeof(unsigned char), width * height * BytesPerPixel, imagefile);
    fclose(imagefile);

    if (!(imagefile = fopen(argv[6], "wb")))
    {
        cout << "Cannot open file: " << argv[6] << endl;
        exit(1);
    }

    //write x-gradient map to file
    fwrite(xGrad, sizeof(unsigned char), width * height, imagefile);
    fclose(imagefile);

    if (!(imagefile = fopen(argv[7], "wb")))
    {
        cout << "Cannot open file: " << argv[7] << endl;
        exit(1);
    }
    
    //write y-gradient map to file
    fwrite(yGrad, sizeof(unsigned char), width * height, imagefile);
    
    fclose(imagefile);

    return 0;
}