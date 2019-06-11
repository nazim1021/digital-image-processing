//Name: Nazim Shaikh
//USC ID: 8711456229
//USC EMAIL: nshaikh@usc.edu
//Submission Date: 02/12/2019

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    FILE *imagefile;
    int BytesPerPixel;
    int width;
    int height;

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

    unsigned char halftonedImage[height][width];

    float extendedImage[height+4][width+4];

    //get extended image
    for (int i = 0; i < height; i++) {
        for (int j =0 ; j < width; j++){
            extendedImage[i+2][j+2] = Imagedata[i][j][0];
        }
    }

    //extend rows
    for (int j = 0; j < width; j++) {
        extendedImage[0][j+2] = Imagedata[2][j][0];
        extendedImage[1][j+2] = Imagedata[1][j][0];
        extendedImage[height+2][j+2] = Imagedata[height-2][j][0];
        extendedImage[height+3][j+2] = Imagedata[height-3][j][0];
    }

    //extend columns
    for (int i = 0; i < height; i++)
    {
        extendedImage[i+2][0] = extendedImage[i][2];
        extendedImage[i+2][1] = extendedImage[i][1];
        extendedImage[i+2][width+2] = extendedImage[i][width-2];
        extendedImage[i+2][width+3] = extendedImage[i][width-3];
    }

    int T = 128;
    for (int i = 2; i < height + 2; i++)
    {
        if ((i - 2) % 2 != 0)
        {
            for (int j = 2; j < width + 2; j++)
            {
                halftonedImage[i - 2][j - 2] = (extendedImage[i][j] > T) ? 255 : 0;

                float err = (extendedImage[i][j] - halftonedImage[i - 2][j - 2])/48.0;

                extendedImage[i][j + 1] += 7 * err;
                extendedImage[i][j + 2] += 5 * err;

                extendedImage[i + 1][j - 2] += 3 * err;
                extendedImage[i + 1][j - 1] += 5 * err;
                extendedImage[i + 1][j] += 7 * err;
                extendedImage[i + 1][j + 1] += 5*err;
                extendedImage[i + 1][j + 2] += 3*err;

                extendedImage[i + 2][j - 2] += 1 * err;
                extendedImage[i + 2][j - 1] += 3 * err;
                extendedImage[i + 2][j] += 5 * err;
                extendedImage[i + 2][j + 1] += 3*err;
                extendedImage[i + 2][j + 2] += err;
            }
        }
        else
        {
            for (int j = width+1; j >= 2; j--)
            {
                halftonedImage[i - 2][j - 2] = (extendedImage[i][j] > T) ? 255 : 0;

                float err = (extendedImage[i][j] - halftonedImage[i - 2][j - 2])/48.0;
                
                extendedImage[i][j - 1] += 7 * err;
                extendedImage[i][j - 2] += 5 * err;

                extendedImage[i + 1][j - 2] += 3 * err;
                extendedImage[i + 1][j - 1] += 5 * err;
                extendedImage[i + 1][j] += 7 * err;
                extendedImage[i + 1][j + 1] += 5*err;
                extendedImage[i + 1][j + 2] += 3*err;

                extendedImage[i + 2][j - 2] += 1 * err;
                extendedImage[i + 2][j - 1] += 3 * err;
                extendedImage[i + 2][j] += 5 * err;
                extendedImage[i + 2][j + 1] += 3*err;
                extendedImage[i + 2][j + 2] += err;
            }
        }
    }

    // Write image data (filename specified by second argument) from image data matrix
    if (!(imagefile = fopen(argv[2], "wb")))
    {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(halftonedImage, sizeof(unsigned char), width * height, imagefile);
    fclose(imagefile);

    return 0;
}