#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <numeric>
#include <vector>

using namespace std;

vector<vector<unsigned char> > extendImage(vector<vector<unsigned char> > Imagedata, int height, int width)
{

    vector<vector<unsigned char>> extendedImage(height+2, vector<unsigned char> (width+2, 0));
    
    //get extended image
    for (int i = 0; i < height; i++) {
        for (int j =0 ; j < width; j++){
            extendedImage[i+1][j+1] = Imagedata[i][j];
        }
    }
    //extend rows
    for (int j = 0; j < width; j++) {
        extendedImage[0][j+1] = Imagedata[1][j];
        extendedImage[height+1][j+1] = Imagedata[height-2][j];
    }

    //extend columns
    for (int i = 0; i < height; i++)
    {
        extendedImage[i+1][0] = extendedImage[i][1];
        extendedImage[i+1][width+1] = extendedImage[i][width-2];
    }

    return extendedImage;
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
    
    unsigned char Imagedata[height][width];
    
    // Read image (filename specified by first argument) into image data matrix
    if (!(imagefile=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), width*height, imagefile);
    fclose(imagefile);
    
    
    vector<std::vector<unsigned char>> BinaryImage(height, vector<unsigned char> (width, 0));
    
    for(int i=0;i<height;i++)
    {
        for(int j=0; j<width; j++)
        {
            if (Imagedata[i][j] >= 128){
                BinaryImage[i][j] = 1;
            }
            else{
                BinaryImage[i][j] = 0;
            }
        }
    }

    vector<vector<unsigned char>> ExtendedImage(height+2, vector<unsigned char> (width+2, 0));
    vector<vector<unsigned char>> FinalImage(height+2, vector<unsigned char> (width+2, 0));
    ExtendedImage = extendImage(BinaryImage, height, width);

    vector <unsigned char> pattern;
    vector <unsigned char> defect_mask {1,1,1,1,0,1,1,1,1};
    vector<int> x;
    vector<int> y;
    int defect_count = 0;
    bool defect;
    for(int i=1;i<height+1;i++)
    {
        for(int j=1;j<width+1;j++)
        {
            pattern.clear();
            for(int m=-1; m<=1; m++)
            {
                for(int n=-1; n<=1; n++)
                { 
                    pattern.push_back(ExtendedImage[i+m][j+n]);
                }
            } 
            bool hit =  (defect_mask == pattern);
            FinalImage[i-1][j-1] = ExtendedImage[i][j];
            if(hit) 
            {   
                defect=true;
                defect_count+=1;
                x.push_back(j);
                y.push_back(i);
                FinalImage[i-1][j-1] = 1;
            }
            // }else{
            //     FinalImage[i-1][j-1] = 0;
            // }
        }
    }
    if(defect){ 
        cout<<"Number of defects found: "<<defect_count<<endl;
        cout << "x-coordinates:";
        for (vector<int>::iterator it = x.begin() ; it != x.end(); ++it)
            std::cout << ' ' << *it;
        cout<<'\n';
        cout << "y-coordinates:";
        for (vector<int>::iterator it = y.begin() ; it != y.end(); ++it)
            std::cout << ' ' << *it;
        cout<<'\n';
    }else{
        cout<<"Image is defectless\n";   
    }

    unsigned char OutputImage[height][width];
    for(int i=0;i<height;i++)
    {
        for(int j=0; j<width; j++)
        {
            if (FinalImage[i][j] == 1) 
                OutputImage[i][j] = 255;
            else
            {
                OutputImage[i][j] = 0;
            }
            
        }
    }
    
    // Write image data (filename specified by second argument) from image data matrix
    if (!(imagefile = fopen(argv[2], "wb")))
    {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(OutputImage, sizeof(unsigned char), width * height, imagefile);
    fclose(imagefile);

    return 0;

}