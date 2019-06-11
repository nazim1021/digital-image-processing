//Non local mean filtering

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;
const double PI  =3.14;

float gauss(int n1,int n2, float a){
    return exp(-(pow(n1,2)+pow(n2,2))/(2*a*a))/(sqrt(2*PI)*a);
}

float filterFunction(unsigned char Image[280][280], int x, int y) {
    float alpha = 1.0;
    float h = 100.0;
    float f_val = 0.0;
    float total_sum = 0.0;
    for(int a = x-10; a<x+11; a++) {
        for (int b = y-10; b < y+11; b++) {
            float f_sum = 0.0;
            for (int k = -2; k <= 2; k++) {
                for (int l = -2; l <= 2; l++) {
                    f_sum += gauss(k, l, alpha) * pow((Image[x+k][y+l] - Image[a+k][b+l]), 2);
                }
            }
            f_val += Image[a][b]*exp(-f_sum/(h*h));

            total_sum+=exp(-f_sum/(h*h));
        }
    }

    float new_pixel = f_val/total_sum;

    return new_pixel;
};

int main(int argc, char *argv[])
{
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel = 1;
    int width = 256;
    int height = 256;

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

    unsigned char extendedImage[280][280];

    //get extended image
    for (int i = 0; i < height; i++) {
        for (int j =0 ; j < width; j++){
            extendedImage[i+12][j+12] = Imagedata[i][j][0];
        }
    }

    //extend rows
    for (int j = 0; j < width; j++) {
        for(int k=0;k<12;k++){
            extendedImage[k][j+12] = Imagedata[12-k][j][0];
            extendedImage[height+k+12][j+12] = Imagedata[height-(k+2)][j][0];
        }
    }

    //extend columns
    for (int i = 0; i < height+24; i++)
    {
        for(int k=0;k<12;k++) {
            extendedImage[i][k] = extendedImage[i][24-k];
            extendedImage[i][width+k+12] = extendedImage[i][width-k+12];
        }
    }

    unsigned char denoiseImage[height][width];

    for (int i = 12; i < height+12; i++)
    {
        for (int j = 12; j < width+12; j++) {

            denoiseImage[i-12][j-12] = filterFunction(extendedImage, i, j);
        }
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
