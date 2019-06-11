//Image denoising for color image with mixed noise

#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>

using namespace std;

int median_filter(unsigned char Image[260][260][3], int x, int y, int k){
    vector<int> medianImg;

    for (int a = 0; a < 5; a++)
    {
        for (int b = 0; b < 5; b++) {
            medianImg.push_back(Image[a+x][b+y][k]);
        }
    }
    sort(medianImg.begin(), medianImg.end());
    size_t size = medianImg.size();
    double median = medianImg[(size+1)/2];

    return median;
}

int main(int argc, char *argv[])
{
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel = 3;
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

    unsigned char extendedImage[260][260][3];

    //get extended image
    for (int i = 0; i < height; i++) {
        for (int j =0 ; j < width; j++){
            for (int k=0; k<3;k++){
                extendedImage[i+2][j+2][k] = Imagedata[i][j][k];
            }
        }
    }

    //extend rows
    for (int j = 0; j < width; j++) {
        for (int k=0; k<3;k++) {
            extendedImage[0][j + 2][k] = Imagedata[2][j][k];
            extendedImage[1][j + 2][k] = Imagedata[1][j][k];
            extendedImage[height + 2][j + 2][k] = Imagedata[height - 2][j][k];
            extendedImage[height + 3][j + 2][k] = Imagedata[height - 3][j][k];
        }
    }

    //extend columns
    for (int i = 0; i < height; i++)
    {
        for (int k=0; k<3;k++) {
            extendedImage[i + 2][0][k] = extendedImage[i][2][k];
            extendedImage[i + 2][1][k] = extendedImage[i][1][k];
            extendedImage[i + 2][width + 2][k] = extendedImage[i][width - 2][k];
            extendedImage[i + 2][width + 3][k] = extendedImage[i][width - 3][k];
        }
    }

    unsigned char denoiseImage[height][width][BytesPerPixel];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k=0; k<3;k++) {

                //apply guassian filter
                denoiseImage[i][j][k] =
                        (extendedImage[i][j][k] + 4 * extendedImage[i][j + 1][k] + 7 * extendedImage[i][j + 2][k] +
                         4 * extendedImage[i][j + 3][k] + extendedImage[i][j + 4][k] +

                         4 * extendedImage[i + 1][j][k] + 16 * extendedImage[i + 1][j + 1][k] +
                         26 * extendedImage[i + 1][j + 2][k] + 16 * extendedImage[i + 1][j + 3][k] +
                         4 * extendedImage[i + 1][j + 4][k] +

                         7 * extendedImage[i + 2][j][k] + 26 * extendedImage[i + 2][j + 1][k] +
                         41 * extendedImage[i + 2][j + 2][k] + 26 * extendedImage[i + 2][j + 3][k] +
                         7 * extendedImage[i + 2][j + 4][k] +

                         4 * extendedImage[i + 3][j][k] + 16 * extendedImage[i + 3][j + 1][k] +
                         26 * extendedImage[i + 3][j + 2][k] + 16 * extendedImage[i + 3][j + 3][k] +
                         4 * extendedImage[i + 3][j + 4][k] +

                         extendedImage[i + 4][j][k] + 4 * extendedImage[i + 4][j + 1][k] + 7 * extendedImage[i + 4][j + 2][k] +
                         4 * extendedImage[i + 4][j + 3][k] + extendedImage[i + 4][j + 4][k]) / 273;
            }
        };
    };

    unsigned char noisyextendedImage[260][260][3];

    //get extended image
    for (int i = 0; i < height; i++) {
        for (int j =0 ; j < width; j++){
            for (int k=0; k<3;k++){
                noisyextendedImage[i+2][j+2][k] = denoiseImage[i][j][k];
            }
        }
    }

    //extend rows
    for (int j = 0; j < width; j++) {
        for (int k=0; k<3;k++) {
            noisyextendedImage[0][j + 2][k] = denoiseImage[2][j][k];
            noisyextendedImage[1][j + 2][k] = denoiseImage[1][j][k];
            noisyextendedImage[height + 2][j + 2][k] = denoiseImage[height - 2][j][k];
            noisyextendedImage[height + 3][j + 2][k] = denoiseImage[height - 3][j][k];
        }
    }

    //extend columns
    for (int i = 0; i < height; i++)
    {
        for (int k=0; k<3;k++) {
            noisyextendedImage[i + 2][0][k] = noisyextendedImage[i][2][k];
            noisyextendedImage[i + 2][1][k] = noisyextendedImage[i][1][k];
            noisyextendedImage[i + 2][width + 2][k] = noisyextendedImage[i][width - 2][k];
            noisyextendedImage[i + 2][width + 3][k] = noisyextendedImage[i][width - 3][k];
        }
    }

    unsigned char finalImage[height][width][BytesPerPixel];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < 3; k++) {
                //apply median filter
                finalImage[i][j][k] = median_filter(noisyextendedImage, i,j,k);
            }
        }
    }

    // Write image data (filename specified by second argument) from ima ge data matrix

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(finalImage, sizeof(unsigned char), width*height*BytesPerPixel, file);
    fclose(file);

    return 0;
}
