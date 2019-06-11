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
    int BytesPerPixel = 1;
    int width = 400;
    int height = 600;

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
    if (!(imagefile=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), width*height*BytesPerPixel, imagefile);
    fclose(imagefile);


    unsigned char halftonedImage[height][width];
    srand(21);
    for (int i=0;i<height; i++){
        for(int j=0;j<width;j++){
            int irand  = rand() % 256;
            if ( 0 <= (unsigned int)Imagedata[i][j][0] and (unsigned int)Imagedata[i][j][0]<irand ){
                halftonedImage[i][j] = (unsigned char)0;
            }
            else{
                halftonedImage[i][j] = (unsigned char)255;
            }
        }
    }

    // Write image data (filename specified by second argument) from image data matrix

    if (!(imagefile=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(halftonedImage, sizeof(unsigned char), width*height*BytesPerPixel, imagefile);
    fclose(imagefile);

    return 0;
}