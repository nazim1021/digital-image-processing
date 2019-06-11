//Shot noise filtering

#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <math.h>

using namespace std;

double shot_filter(int pixel){
    return 2*sqrt(pixel+3/8);

}

double inverse_shot_filter(int pixel){
    return pixel * pixel / 4 - 3 / 8;

}

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

    unsigned char extendedImage[height+4][width+4];

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

    unsigned char denoiseImage[height][width];
    unsigned char shotImage[height][width];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            shotImage[i][j] = shot_filter(extendedImage[i][j]);
        }
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            denoiseImage[i][j] = (shotImage[i][j] + 4*shotImage[i][j+1] + 7*shotImage[i][j+2]+ 4*shotImage[i][j+3] + shotImage[i][j+4]+
                                  4*shotImage[i+1][j]+16*shotImage[i+1][j+1]+ 26*shotImage[i+1][j+2]+16*shotImage[i+1][j+3]+4*shotImage[i+1][j+4]+
                                  7*shotImage[i+2][j]+26*shotImage[i+2][j+1]+ 41*shotImage[i+2][j+2]+26*shotImage[i+2][j+3]+7*shotImage[i+2][j+4]+
                                  4*shotImage[i+3][j]+16*shotImage[i+3][j+1]+ 26*shotImage[i+3][j+2]+16*shotImage[i+3][j+3]+4*shotImage[i+3][j+4]+
                    shotImage[i+4][j] + 4*shotImage[i+4][j+1] + 7*shotImage[i+4][j+2]+ 4*shotImage[i+4][j+3] + shotImage[i+4][j+4])/273;
        };
    };
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            denoiseImage[i][j] = inverse_shot_filter(denoiseImage[i][j]);
        }
    }

    // Write image data (filename specified by second argument) from ima ge data matrix

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }

    fwrite(denoiseImage, sizeof(unsigned char), width*height*BytesPerPixel, file);
    fclose(file);

    return 0;
}
