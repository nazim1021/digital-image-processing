//Transfer function based histogram manipulation

#include <stdio.h>
#include <iostream>
#include <map>
#include <stdlib.h>
#include <fstream>

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
    std::map<int, float> histmap;
    unsigned char histImage[height][width];


    //get histogram
    for (int k = 0; k < 256; k++) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (k == (unsigned int) Imagedata[i][j][0]) {
                    histmap[k] = histmap[k] + 1;

                }
            }
        }
    }

    //normalize histogram
    ofstream myfile("hist.csv");
    if (myfile.is_open()) {
    for (int k=0;k<256;k++) {
        myfile<<k<<","<<histmap[k]<<endl;
        histmap[k] = histmap[k]/(height*width);
    }   myfile.close();
    }
    //get cdf
    for (int k =1;k<256;k++){
        histmap[k]=histmap[k]+histmap[k-1];
    }
    ofstream cdffile("cdf.csv");
    if (myfile.is_open())
    {
    //get equalized image
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            histImage[i][j] = histmap[(unsigned int)Imagedata[i][j][0]]*255;
            cdffile<<(unsigned int)Imagedata[i][j][0]<<","<<histmap[(unsigned int)Imagedata[i][j][0]]*255<<endl;
            }
        }
        cdffile.close();
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
