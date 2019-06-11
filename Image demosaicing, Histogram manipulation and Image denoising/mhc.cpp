//Name: Nazim Shaikh
//USC ID: 8711456229
//USC EMAIL: nshaikh@usc.edu
//Submission Date: 01/22/2019



// This code implements MHC demosaicing

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])
{
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel = 1;
    int channels = 3;
    int width = 390;
    int height = 300;

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


    unsigned char demosaicImage[height][width][channels];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //even row
            if(i%2==0 ){
                //even column
                if (j%2==0){
                    //red at green with red row and blue column
                    demosaicImage[i][j][0] = (-1*extendedImage[i+2][j] + 4*extendedImage[i+2][j+1] + 5*extendedImage[i+2][j+2]+
                            4*extendedImage[i+2][j+3]-1*extendedImage[i+2][j+4] -1 *extendedImage[i+1][j+1]-1*extendedImage[i+3][j+1]
                            -1 *extendedImage[i+1][j+3]-1*extendedImage[i+3][j+3] + 0.5*extendedImage[i][j+2]+0.5*extendedImage[i+4][j+2] )/8;

                    //green
                    demosaicImage[i][j][1] = extendedImage[i+2][j+2];

                    //blue at green with red row and blue column
                    demosaicImage[i][j][2] = (0.5*extendedImage[i+2][j] + 4*extendedImage[i+1][j+2] + 5*extendedImage[i+2][j+2]+
                                              4*extendedImage[i+3][j+2] + 0.5*extendedImage[i+2][j+4] -1 *extendedImage[i][j+2] -1*extendedImage[i+4][j+2]
                                              -1 *extendedImage[i+1][j+1]-1*extendedImage[i+3][j+1] -1*extendedImage[i+1][j+3] -1*extendedImage[i+3][j+3] )/8;
                }
                //odd column
                else{
                    //red
                    demosaicImage[i][j][0] = extendedImage[i+2][j+2];
                    //green at red
                    demosaicImage[i][j][1] = (-1*extendedImage[i+2][j] + 2*extendedImage[i+2][j+1] + 4*extendedImage[i+2][j+2]+
                                              2*extendedImage[i+2][j+3]-1*extendedImage[i+2][j+4] -1 *extendedImage[i][j+2]+2*extendedImage[i+1][j+2]
                                              +2 *extendedImage[i+3][j+2]-1*extendedImage[i+4][j+2])/8;
                    //blue at red
                    demosaicImage[i][j][2] = (-1.5*extendedImage[i+2][j] + 6*extendedImage[i+2][j+2]+
                                              -1.5*extendedImage[i+2][j+4] +2*extendedImage[i+1][j+1]+2*extendedImage[i+3][j+1]
                                              +2 *extendedImage[i+1][j+3]+2*extendedImage[i+3][j+3] -1.5*extendedImage[i][j+2]-1.5*extendedImage[i+4][j+2] )/8;
                }
            }
            //odd row
            else{
                //even column
                if (j%2==0){
                    //red at blue
                    demosaicImage[i][j][0] = (-1.5*extendedImage[i+2][j] + 6*extendedImage[i+2][j+2]+
                                              -1.5*extendedImage[i+2][j+4] +2*extendedImage[i+1][j+1]+2*extendedImage[i+3][j+1]
                                              +2 *extendedImage[i+1][j+3]+2*extendedImage[i+3][j+3] -1.5*extendedImage[i][j+2]-1.5*extendedImage[i+4][j+2] )/8;
                    //green at blue
                    demosaicImage[i][j][1] = (-1*extendedImage[i+2][j] + 2*extendedImage[i+2][j+1] + 4*extendedImage[i+2][j+2]+
                                              2*extendedImage[i+2][j+3]-1*extendedImage[i+2][j+4] -1 *extendedImage[i][j+2]+2*extendedImage[i+1][j+2]
                                              +2 *extendedImage[i+3][j+2]-1*extendedImage[i+4][j+2])/8;
                    //blue
                    demosaicImage[i][j][2] = extendedImage[i+2][j+2];
                }
                //odd column
                else{
                    //red at green
                    demosaicImage[i][j][0] = (0.5*extendedImage[i+2][j] + 4*extendedImage[i+1][j+2] + 5*extendedImage[i+2][j+2]+
                                              4*extendedImage[i+3][j+2] + 0.5*extendedImage[i+2][j+4] -1 *extendedImage[i][j+2] -1*extendedImage[i+4][j+2]
                                              -1 *extendedImage[i+1][j+1]-1*extendedImage[i+3][j+1] -1*extendedImage[i+1][j+3] -1*extendedImage[i+3][j+3] )/8;

                    //green
                    demosaicImage[i][j][1] = extendedImage[i+2][j+2];

                    //blue at green
                    demosaicImage[i][j][2] = (-1*extendedImage[i+2][j] + 4*extendedImage[i+2][j+1] + 5*extendedImage[i+2][j+2]+
                                              4*extendedImage[i+2][j+3]-1*extendedImage[i+2][j+4] -1 *extendedImage[i+1][j+1]-1*extendedImage[i+3][j+1]
                                              -1 *extendedImage[i+1][j+3]-1*extendedImage[i+3][j+3] + 0.5*extendedImage[i][j+2]+0.5*extendedImage[i+4][j+2] )/8;
                }
            }
        };
    };

    // Write image data (filename specified by second argument) from ima ge data matrix

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(demosaicImage, sizeof(unsigned char), width*height*3, file);
    fclose(file);

    return 0;
}
