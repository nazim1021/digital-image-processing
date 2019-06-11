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

// Returns true if x is in range [low..high], else false 
bool inRange(unsigned low, unsigned high, unsigned x) 
{ 
    return  ((x-low) <= (high-low)); 
} 

int **get_dithering_matrix(int ind, int **prev_matrix){
    int **ind_matrix = 0;

    ind_matrix = new int*[ind];
    for(int i=0; i<ind; i++){
        ind_matrix[i] = new int[ind];
        for(int j =0; j<ind; j++){
            ind_matrix[i][j]  =   0; 
        }
    }
    std::vector<int> z(ind);
    std::iota(std::begin(z), std::end(z), 0);

    for (int x = 0; x < ind; x++){
        for(int y = 0; y < ind; y++){ 
                if(inRange(z[0], z[ind/2-1],x) and inRange(z[0], z[ind/2-1],y)){
                    ind_matrix[x][y] = 4*prev_matrix[x%(ind/2)][y%(ind/2)]+1;
                }
                else if(inRange(z[0], z[ind/2-1],x) and inRange(z[ind], z[2*ind/2-1],y)){
                    ind_matrix[x][y] = 4*prev_matrix[x%(ind/2)][y%(ind/2)]+2;
                }
                else if(inRange(z[0], z[ind/2-1],y) and inRange(z[ind/2], z[2*ind/2-1],x)){
                    ind_matrix[x][y] = 4*prev_matrix[x%(ind/2)][y%(ind/2)]+3;
                }
                else if(inRange(z[ind], z[2*ind/2-1],x) and inRange(z[ind/2], z[2*ind/2-1],y)){
                    ind_matrix[x][y] = 4*prev_matrix[x%(ind/2)][y%(ind/2)];
                }
        }
    }
    return ind_matrix;

}


int main(int argc, char *argv[])
{
    FILE *imagefile;
    int BytesPerPixel;
    int width;
    int height;

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
     
    int ind = 4;
    int k =2;
    int **ind_matrix;
    ind_matrix = new int*[2];
    for(int i=0; i<2; i++){
        ind_matrix[i] = new int[ind];
        for(int j =0; j<2; j++){
            ind_matrix[i][j]  =   0; 
        }
    }
    while(k<=ind){
        ind_matrix = get_dithering_matrix(k, ind_matrix);    
        k = k*2;    
    }

    float Thresh_matrix[ind][ind];
    for (int x = 0; x < ind; x++){
        for(int y = 0; y < ind; y++){
                Thresh_matrix[x][y] = (int)(255*(ind_matrix[x][y]+0.5)/(ind*ind));   
        }
    }

    for (int i=0;i<height; i++){
        for(int j=0;j<width;j++){

            halftonedImage[i][j] = (0 <= (unsigned int)Imagedata[i][j][0] and (unsigned int)Imagedata[i][j][0]<=Thresh_matrix[i%ind][j%ind])
                ? (unsigned char)0 : (unsigned char)255;           
        }
    }

    // Write image data (filename specified by second argument) from image data matrix
    if (!(imagefile=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(halftonedImage, sizeof(unsigned char), width*height, imagefile);
    fclose(imagefile);

    return 0;
}