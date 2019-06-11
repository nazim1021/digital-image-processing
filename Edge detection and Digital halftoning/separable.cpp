//Name: Nazim Shaikh
//USC ID: 8711456229
//USC EMAIL: nshaikh@usc.edu
//Submission Date: 02/12/2019

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

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

    float extendedImage[height + 2][width + 2][BytesPerPixel];

    //get extended image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            extendedImage[i + 1][j + 1][0] = 255 - (unsigned int)Imagedata[i][j][0];
            extendedImage[i + 1][j + 1][1] = 255 - (unsigned int)Imagedata[i][j][1];
            extendedImage[i + 1][j + 1][2] = 255 - (unsigned int)Imagedata[i][j][2];
        }
    }

    //extend rows
    for (int j = 0; j < width; j++)
    {
        for(int k = 0; k<BytesPerPixel; k++){
            extendedImage[0][j + 1][k] = 255 - (unsigned int)Imagedata[1][j][k];  
            extendedImage[height + 1][j + 1][k] = 255 - (unsigned int)Imagedata[height-2][j][k];  
        }
    }

    //extend columns
    for (int i = 0; i < height + 2; i++)
    {
        for(int k = 0; k<BytesPerPixel; k++){
            extendedImage[i + 1][0][k] = extendedImage[i][1][k];
            extendedImage[i + 1][width + 1][k] = extendedImage[i][width - 2][k];
        }
    }
    
    unsigned char halftonedImage[height][width][BytesPerPixel];

    int T = 128;
    for (int i = 1; i < height + 1; i++)
    {
        if ((i-1) % 2 == 0)
        {
            for (int j = 1; j < width + 1; j++)
            {
                for (int k = 0; k < BytesPerPixel; k++)
                {
                    halftonedImage[i - 1][j - 1][k] = (extendedImage[i][j][k] > T) ? 255 : 0;

                    float err = (extendedImage[i][j][k] - halftonedImage[i - 1][j - 1][k])/16.0;

                    extendedImage[i][j + 1][k] += 7 * err;
                    extendedImage[i + 1][j - 1][k] += 1 * err;
                    extendedImage[i + 1][j][k] += 5 * err;
                    extendedImage[i + 1][j + 1][k] += 3*err;
                }
            }
        }        
        else
        { 
            for (int j = width; j >= 1; j--)
            {
                for (int k = 0; k < BytesPerPixel; k++)
                {
                    halftonedImage[i - 1][j - 1][k] = (extendedImage[i][j][k] > T) ? 255 : 0;

                    float err = (extendedImage[i][j][k] - halftonedImage[i - 1][j - 1][k])/16.0;

                    extendedImage[i][j - 1][k] += 7 * err;
                    extendedImage[i + 1][j - 1][k] += err;
                    extendedImage[i + 1][j][k] += 5 * err ;
                    extendedImage[i + 1][j + 1][k] += 3 * err;
                }
            }
        }
    }

    //convert image back to rgb
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            halftonedImage[i][j][0] = 255 - (unsigned int)halftonedImage[i][j][0];
            halftonedImage[i][j][1] = 255 - (unsigned int)halftonedImage[i][j][1];
            halftonedImage[i][j][2] = 255 - (unsigned int)halftonedImage[i][j][2];
        }
    }

    // Write image data (filename specified by second argument) from image data matrix
    if (!(imagefile = fopen(argv[2], "wb")))
    {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(halftonedImage, sizeof(unsigned char), (width) * (height) * BytesPerPixel, imagefile);
    fclose(imagefile);

    return 0;
}