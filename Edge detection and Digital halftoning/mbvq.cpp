//Name: Nazim Shaikh
//USC ID: 8711456229
//USC EMAIL: nshaikh@usc.edu
//Submission Date: 02/12/2019

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;

std::vector<int> getVertexArray(string vertex)
{
    std::vector<int> v;

    if (vertex == "yellow")
    {
        v.push_back(255);
        v.push_back(255);
        v.push_back(0);
    }
    if (vertex == "magenta")
    {
        v.push_back(255);
        v.push_back(0);
        v.push_back(255);
    }
    if (vertex == "cyan")
    {
        v.push_back(0);
        v.push_back(255);
        v.push_back(255);
    }
    if (vertex == "red")
    {
        v.push_back(255);
        v.push_back(0);
        v.push_back(0);
    }
    if (vertex == "blue")
    {
        v.push_back(0);
        v.push_back(0);
        v.push_back(255);
    }
    if (vertex == "green")
    {
        v.push_back(0);
        v.push_back(255);
        v.push_back(0);
    }
    if(vertex == "white"){
        v.push_back(255);
        v.push_back(255);
        v.push_back(255);
    }
    if(vertex == "black"){
        v.push_back(0);
        v.push_back(0);
        v.push_back(0);
    }
    return v;
}

string mbvq(int R, int G, int B)
{
    if ((R + G) > 255)
    {
        if ((G + B) > 255)
        {
            return ((R+G+B)>510) ? "CMYW" : "MYGC";
        }
        else
        {
            return "RGMY";
        }
    }
    else
    {
        if (!((G + B) > 255))
        {
            return !((R + G + B) > 255) ? "KRGB" : "RGBM";
        }
        else
        {
            return "CMGB";
        }
    }
}

string getNearestVertex(string mbvq, int R, int G, int B)
{
    //No.1 for CMYW
    string vertex;

    if (mbvq == "CMYW")
    {
        vertex = "white";
        if (B < 128)
        {
            if (B <= R)
            {
                if (B <= G)
                {
                    vertex = "yellow";
                }
            }
        }
        if (G < 128)
        {
            if (G <= B)
            {
                if (G <= R)
                {
                    vertex = "magenta";
                }
            }
        }
        if (R < 128)
        {
            if (R <= B)
            {
                if (R <= G)
                {
                    vertex = "cyan";
                }
            }
        }
    }

    //No.2 for MYGC
    if (mbvq == "MYGC")
    {
        vertex = "magenta";
        if (G >= B)
        {
            if (R >= B)
            {
                vertex = (R >= 128) ? "yellow":"green";
            }
        }
        if (G >= R)
        {
            if (B >= R)
            {
                vertex = (B >= 128) ? "cyan":"green";
            }
        }
    }

    //No.3 for RGMY
    if (mbvq == "RGMY")
    {
        if (B > 128)
        {
            if (R > 128)
            {
                vertex = (B >= G) ? "magenta":"yellow";
            }
            else
            {
                vertex = (G > B + R ) ? "green":"magenta";
            }
        }
        else
        {
            if (R >= 128)
            {
                vertex = (G >= 128) ? "yellow":"red";
            }
            else
            {
                vertex = (R >= G) ? "red":"green";
            }
        }
    }

    //No.4 for KRGB
    if (mbvq == "KRGB")
    {
        vertex = "black";
        if (B > 128)
        {
            if (B >= R)
            {
                if (B >= G)
                {
                    vertex = "blue";
                }
            }
        }
        if (G > 128)
        {
            if (G >= B)
            {
                if (G >= R)
                {
                    vertex = "green";
                }
            }
        }
        if (R > 128)
        {
            if (R >= B)
            {
                if (R >= G)
                {
                    vertex = "red";
                }
            }
        }
    }

    //No.5 for RGBM
    if (mbvq == "RGBM")
    {
        vertex = "green";
        if (R > G)
        {
            if (R >= B)
            {
                vertex = (B < 128) ? "red":"magenta";
            }
        }
        if (B > G)
        {
            if (B >= R)
            {
                vertex = (R < 128) ? "blue":"magenta";
            }
        }
    }

    //No.6 for CMGB
    if (mbvq == "CMGB")
    {
        if (B > 128)
        {
            if (R > 128)
            {
                vertex = (G >= R ) ? "cyan":"magenta";
            }
            else
            {
                vertex = (G > 128) ? "cyan" : "blue";
            }
        }
        else
        {
            if (R > 128)
            {
                vertex = (R - G + B >=  128) ? "magenta" : "green";
            }
            else
            {
                vertex = (G >=  B) ? "green" : "blue";
            }
        }
    }
    return vertex;
}

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
            extendedImage[i + 1][j + 1][0] = Imagedata[i][j][0];
            extendedImage[i + 1][j + 1][1] = Imagedata[i][j][1];
            extendedImage[i + 1][j + 1][2] = Imagedata[i][j][2];
        }
    }

    //extend rows
    for (int j = 0; j < width; j++)
    {
        for(int k=0; k< BytesPerPixel; k++){
            extendedImage[0][j + 1][k] = Imagedata[1][j][k];    
            extendedImage[height + 1][j + 1][k] = Imagedata[height - 2][j][k];
        }
    }

    //extend columns
    for (int i = 0; i < height + 2; i++)
    {
        for(int k=0; k< BytesPerPixel; k++){
            extendedImage[i + 1][0][k] = extendedImage[i][1][k];    
            extendedImage[i + 1][width + 1][k] = extendedImage[i][width - 2][k];
        }
    }

    unsigned char halftonedImage[height][width][BytesPerPixel];

    for (int i = 1; i < height + 1; i++)
    {
        if ((i - 1) % 2 == 0)
        {
            for (int j = 1; j < width + 1; j++)
            {
                string mb = mbvq(Imagedata[i-1][j-1][0], Imagedata[i-1][j-1][1], Imagedata[i-1][j-1][2]);
                string vertex = getNearestVertex(mb, extendedImage[i][j][0], extendedImage[i][j][1], extendedImage[i][j][2]);
                vector<int> v = getVertexArray(vertex);
                for (int k = 0; k < BytesPerPixel; k++)
                {   
                    halftonedImage[i-1][j-1][k] = v[k];
                    float err = (extendedImage[i][j][k] - v[k])/16.0;
                    extendedImage[i][j + 1][k] += 7.0 * err;
                    extendedImage[i + 1][j - 1][k] +=  1.0* err;
                    extendedImage[i + 1][j][k] += 5.0 * err;
                    extendedImage[i + 1][j + 1][k] += 3.0*err;
                }
            }
        }
        else
        {
            for (int j = width; j >= 1; j--)
            {
                string mb = mbvq(Imagedata[i-1][j-1][0], Imagedata[i-1][j-1][1], Imagedata[i-1][j-1][2]);
                string vertex = getNearestVertex(mb, extendedImage[i][j][0], extendedImage[i][j][1], extendedImage[i][j][2]);
                vector<int> v = getVertexArray(vertex);
                for (int k = 0; k < BytesPerPixel; k++)
                {
                    halftonedImage[i-1][j-1][k] = v[k];
                    float err = (extendedImage[i][j][k] - v[k])/16.0;

                    extendedImage[i][j - 1][k] += 7.0 * err;
                    extendedImage[i + 1][j - 1][k] += 1.0 * err;
                    extendedImage[i + 1][j][k] += 5.0 * err;
                    extendedImage[i + 1][j + 1][k] += 3.0 * err;
                }
            }
        }
    }


    // Write image data (filename specified by second argument) from image data matrix
    if (!(imagefile = fopen(argv[2], "wb")))
    {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(halftonedImage, sizeof(unsigned char), (width)*(height)*BytesPerPixel, imagefile);
    fclose(imagefile);

    return 0;
}