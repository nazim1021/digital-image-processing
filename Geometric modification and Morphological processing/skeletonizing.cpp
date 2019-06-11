//EE569 Homework Assignment #3 Prob 2 Morphological Processing (Shrinking)
//Name: Nazim Shaikh
//USC ID: 8711456229
//USC EMAIL: nshaikh@usc.edu
//Submission Date: 03/03/2019

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

bool ApplyCondMark(vector<unsigned char> pattern)
{
    vector<vector<unsigned char> > markPatterns {
            {0, 1, 0, 0, 1, 1, 0, 0, 0},
            {0, 1, 0, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 1, 0},
            {0, 0, 0, 0, 1, 1, 0, 1, 0},
            {0, 0, 1, 0, 1, 1, 0, 0, 1},
            {1, 1, 1, 0, 1, 0, 0, 0, 0},
            {1, 0, 0, 1, 1, 0, 1, 0, 0},
            {0, 0, 0, 0, 1, 0, 1, 1, 1},
            {1, 1, 1, 0, 1, 1, 0, 0, 0},
            {0, 1, 1, 0, 1, 1, 0, 0, 1},
            {1, 1, 1, 1, 1, 0, 0, 0, 0},
            {1, 1, 0, 1, 1, 0, 1, 0, 0},
            {1, 0, 0, 1, 1, 0, 1, 1, 0},
            {0, 0, 0, 1, 1, 0, 1, 1, 1},
            {0, 0, 0, 0, 1, 1, 1, 1, 1},
            {0, 0, 1, 0, 1, 1, 0, 1, 1},
            {1, 1, 1, 0, 1, 1, 0, 0, 1},
            {1, 1, 1, 1, 1, 0, 1, 0, 0},
            {1, 0, 0, 1, 1, 0, 1, 1, 1},
            {0, 0, 1, 0, 1, 1, 1, 1, 1},
            {0, 1, 1, 0, 1, 1, 0, 1, 1},
            {1, 1, 1, 1, 1, 1, 0, 0, 0},
            {1, 1, 0, 1, 1, 0, 1, 1, 0},
            {0, 0, 0, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 0, 1, 1, 0, 1, 1},
            {0, 1, 1, 0, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 0, 0},
            {1, 1, 1, 1, 1, 1, 0, 0, 1},
            {1, 1, 1, 1, 1, 0, 1, 1, 0},
            {1, 1, 0, 1, 1, 0, 1, 1, 1},
            {1, 0, 0, 1, 1, 1, 1, 1, 1},
            {0, 0, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 0, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 0, 1},
            {1, 1, 1, 1, 1, 0, 1, 1, 1},
            {1, 0, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 0, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 0},
            {1, 1, 0, 1, 1, 1, 1, 1, 1},
            {0, 1, 1, 1, 1, 1, 1, 1, 1}

    };

    for(int i=0;i<markPatterns.size();i++)
    {    
        if(markPatterns[i] == pattern){
            return true;
        } 
    }
    return false;
}

bool ApplyUncondMark(vector<unsigned char> pattern)
{
    vector<vector<unsigned char>> markPatterns{
            {0, 0, 0, 0, 1, 0, 0, 0, 1},
            {0, 0, 0, 0, 1, 0, 1, 0, 0},
            {0, 0, 1, 0, 1, 0, 0, 0, 0},
            {1, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 1, 0},
            {0, 0, 0, 0, 1, 1, 0, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 0, 0},
            {0, 1, 0, 0, 1, 0, 0, 0, 0},
            {0, 1, 0, 0, 1, 1, 0, 0, 0},
            {0, 1, 0, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 0, 1, 0},
            {0, 0, 0, 1, 1, 0, 0, 1, 0},
            {0, 1, 0, 0, 1, 1, 1, 0, 0},
            {0, 1, 0, 1, 1, 0, 0, 0, 1},
            {0, 0, 1, 1, 1, 0, 0, 1, 0},
            {1, 0, 0, 0, 1, 1, 0, 1, 0},
            {1, 1, 0, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 0, 1, 1},
            {0, 1, 0, 1, 1, 1, 0, 0, 0},
            {0, 1, 0, 1, 1, 0, 0, 1, 0},
            {0, 0, 0, 1, 1, 1, 0, 1, 0},
            {0, 1, 0, 0, 1, 1, 0, 1, 0},
            {1, 1, 0, 1, 1, 0, 0, 0, 1},
            {0, 0, 0, 0, 1, 1, 1, 1, 1},
            {0, 1, 0, 1, 1, 1, 0, 0, 1},
            {0, 1, 0, 1, 1, 0, 0, 1, 1},
            {0, 0, 0, 1, 1, 1, 0, 1, 1},
            {0, 1, 0, 0, 1, 1, 0, 1, 1},
            {1, 1, 0, 1, 1, 0, 0, 1, 0},
            {0, 0, 0, 1, 1, 1, 0, 1, 1},
            {0, 1, 0, 1, 1, 1, 0, 1, 0},
            {0, 1, 0, 1, 1, 0, 1, 1, 0},
            {0, 0, 0, 1, 1, 1, 1, 1, 0},
            {0, 1, 0, 0, 1, 1, 1, 1, 0},
            {1, 1, 0, 1, 1, 0, 0, 1, 1},
            {0, 0, 0, 1, 1, 1, 1, 1, 1},
            {0, 1, 0, 1, 1, 1, 0, 1, 1},
            {0, 1, 0, 1, 1, 0, 1, 1, 1},
            {0, 0, 0, 1, 1, 1, 1, 1, 1},
            {0, 1, 0, 0, 1, 1, 1, 1, 1},
            {1, 1, 0, 1, 1, 0, 1, 0, 0},
            {0, 0, 1, 0, 1, 1, 0, 1, 1},
            {0, 1, 0, 1, 1, 1, 1, 0, 0},
            {0, 1, 0, 1, 1, 1, 0, 1, 0},
            {0, 0, 1, 1, 1, 1, 0, 1, 0},
            {0, 1, 0, 1, 1, 1, 0, 1, 0},
            {1, 1, 0, 1, 1, 0, 1, 0, 1},
            {0, 0, 1, 0, 1, 1, 1, 1, 1},
            {0, 1, 0, 1, 1, 1, 1, 0, 1},
            {0, 1, 0, 1, 1, 1, 0, 1, 1},
            {0, 0, 1, 1, 1, 1, 0, 1, 1},
            {0, 1, 0, 1, 1, 1, 0, 1, 1},
            {1, 1, 0, 1, 1, 0, 1, 1, 0},
            {0, 0, 1, 1, 1, 1, 0, 1, 1},
            {0, 1, 0, 1, 1, 1, 1, 1, 0},
            {0, 1, 0, 1, 1, 1, 1, 1, 0},
            {0, 0, 1, 1, 1, 1, 1, 1, 0},
            {0, 1, 0, 1, 1, 1, 1, 1, 0},
            {1, 1, 0, 1, 1, 0, 1, 1, 1},
            {0, 0, 1, 1, 1, 1, 1, 1, 1},
            {0, 1, 0, 1, 1, 1, 1, 1, 1},
            {0, 1, 0, 1, 1, 1, 1, 1, 1},
            {0, 0, 1, 1, 1, 1, 1, 1, 1},
            {0, 1, 0, 1, 1, 1, 1, 1, 1},
            {0, 1, 0, 0, 1, 1, 1, 0, 1},
            {0, 1, 0, 1, 1, 0, 1, 0, 1},
            {0, 0, 1, 1, 1, 0, 0, 1, 1},
            {1, 0, 0, 0, 1, 1, 1, 1, 0},
            {1, 1, 0, 1, 1, 1, 0, 0, 0},
            {0, 1, 0, 0, 1, 1, 0, 1, 1},
            {0, 1, 1, 1, 1, 1, 0, 0, 0},
            {0, 1, 1, 1, 1, 0, 0, 1, 0},
            {0, 1, 0, 1, 1, 1, 0, 1, 0},
            {0, 1, 1, 0, 1, 1, 0, 1, 0},
            {1, 1, 0, 1, 1, 1, 0, 0, 1},
            {0, 1, 0, 0, 1, 1, 1, 1, 1},
            {0, 1, 1, 1, 1, 1, 0, 0, 1},
            {0, 1, 1, 1, 1, 0, 0, 1, 1},
            {0, 1, 0, 1, 1, 1, 0, 1, 1},
            {0, 1, 1, 0, 1, 1, 0, 1, 1},
            {1, 1, 0, 1, 1, 1, 0, 1, 0},
            {0, 1, 0, 1, 1, 1, 0, 1, 1},
            {0, 1, 1, 1, 1, 1, 0, 1, 0},
            {0, 1, 1, 1, 1, 0, 1, 1, 0},
            {0, 1, 0, 1, 1, 1, 1, 1, 0},
            {0, 1, 1, 0, 1, 1, 1, 1, 0},
            {1, 1, 0, 1, 1, 1, 0, 1, 1},
            {0, 1, 0, 1, 1, 1, 1, 1, 1},
            {0, 1, 1, 1, 1, 1, 0, 1, 1},
            {0, 1, 1, 1, 1, 0, 1, 1, 1},
            {0, 1, 0, 1, 1, 1, 1, 1, 1},
            {0, 1, 1, 0, 1, 1, 1, 1, 1},
            {1, 1, 0, 1, 1, 1, 1, 0, 0},
            {0, 1, 1, 0, 1, 1, 0, 1, 1},
            {0, 1, 1, 1, 1, 1, 1, 0, 0},
            {0, 1, 1, 1, 1, 1, 0, 1, 0},
            {0, 1, 1, 1, 1, 1, 0, 1, 0},
            {0, 1, 1, 1, 1, 1, 0, 1, 0},
            {1, 1, 0, 1, 1, 1, 1, 0, 1},
            {0, 1, 1, 0, 1, 1, 1, 1, 1},
            {0, 1, 1, 1, 1, 1, 1, 0, 1},
            {0, 1, 1, 1, 1, 1, 0, 1, 1},
            {0, 1, 1, 1, 1, 1, 0, 1, 1},
            {0, 1, 1, 1, 1, 1, 0, 1, 1},
            {1, 1, 0, 1, 1, 1, 1, 1, 0},
            {0, 1, 1, 1, 1, 1, 0, 1, 1},
            {0, 1, 1, 1, 1, 1, 1, 1, 0},
            {0, 1, 1, 1, 1, 1, 1, 1, 0},
            {0, 1, 1, 1, 1, 1, 1, 1, 0},
            {0, 1, 1, 1, 1, 1, 1, 1, 0},
            {1, 1, 0, 1, 1, 1, 1, 1, 1},
            {0, 1, 1, 1, 1, 1, 1, 1, 1},
            {0, 1, 1, 1, 1, 1, 1, 1, 1},
            {0, 1, 1, 1, 1, 1, 1, 1, 1},
            {0, 1, 1, 1, 1, 1, 1, 1, 1},
            {0, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 0, 0, 1, 1, 1, 0, 0},
            {0, 1, 1, 1, 1, 0, 0, 0, 1},
            {1, 0, 1, 1, 1, 0, 0, 1, 0},
            {1, 0, 1, 0, 1, 1, 0, 1, 0},
            {1, 1, 1, 1, 1, 0, 0, 0, 0},
            {1, 0, 0, 0, 1, 1, 0, 1, 1},
            {1, 1, 0, 1, 1, 1, 0, 0, 0},
            {1, 1, 0, 1, 1, 0, 0, 1, 0},
            {1, 0, 0, 1, 1, 1, 0, 1, 0},
            {1, 1, 0, 0, 1, 1, 0, 1, 0},
            {1, 1, 1, 1, 1, 0, 0, 0, 1},
            {1, 0, 0, 0, 1, 1, 1, 1, 1},
            {1, 1, 0, 1, 1, 1, 0, 0, 1},
            {1, 1, 0, 1, 1, 0, 0, 1, 1},
            {1, 0, 0, 1, 1, 1, 0, 1, 1},
            {1, 1, 0, 0, 1, 1, 0, 1, 1},
            {1, 1, 1, 1, 1, 0, 0, 1, 0},
            {1, 0, 0, 1, 1, 1, 0, 1, 1},
            {1, 1, 0, 1, 1, 1, 0, 1, 0},
            {1, 1, 0, 1, 1, 0, 1, 1, 0},
            {1, 0, 0, 1, 1, 1, 1, 1, 0},
            {1, 1, 0, 0, 1, 1, 1, 1, 0},
            {1, 1, 1, 1, 1, 0, 0, 1, 1},
            {1, 0, 0, 1, 1, 1, 1, 1, 1},
            {1, 1, 0, 1, 1, 1, 0, 1, 1},
            {1, 1, 0, 1, 1, 0, 1, 1, 1},
            {1, 0, 0, 1, 1, 1, 1, 1, 1},
            {1, 1, 0, 0, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 0, 1, 0, 0},
            {1, 0, 1, 0, 1, 1, 0, 1, 1},
            {1, 1, 0, 1, 1, 1, 1, 0, 0},
            {1, 1, 0, 1, 1, 1, 0, 1, 0},
            {1, 0, 1, 1, 1, 1, 0, 1, 0},
            {1, 1, 0, 1, 1, 1, 0, 1, 0},
            {1, 1, 1, 1, 1, 0, 1, 0, 1},
            {1, 0, 1, 0, 1, 1, 1, 1, 1},
            {1, 1, 0, 1, 1, 1, 1, 0, 1},
            {1, 1, 0, 1, 1, 1, 0, 1, 1},
            {1, 0, 1, 1, 1, 1, 0, 1, 1},
            {1, 1, 0, 1, 1, 1, 0, 1, 1},
            {1, 1, 1, 1, 1, 0, 1, 1, 0},
            {1, 0, 1, 1, 1, 1, 0, 1, 1},
            {1, 1, 0, 1, 1, 1, 1, 1, 0},
            {1, 1, 0, 1, 1, 1, 1, 1, 0},
            {1, 0, 1, 1, 1, 1, 1, 1, 0},
            {1, 1, 0, 1, 1, 1, 1, 1, 0},
            {1, 1, 1, 1, 1, 0, 1, 1, 1},
            {1, 0, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 0, 1, 1, 1, 1, 1, 1},
            {1, 1, 0, 1, 1, 1, 1, 1, 1},
            {1, 0, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 0, 1, 1, 1, 1, 1, 1},
            {1, 1, 0, 0, 1, 1, 1, 0, 1},
            {0, 1, 1, 1, 1, 0, 1, 0, 1},
            {1, 0, 1, 1, 1, 0, 0, 1, 1},
            {1, 0, 1, 0, 1, 1, 1, 1, 0},
            {1, 1, 1, 1, 1, 1, 0, 0, 0},
            {1, 1, 0, 0, 1, 1, 0, 1, 1},
            {1, 1, 1, 1, 1, 1, 0, 0, 0},
            {1, 1, 1, 1, 1, 0, 0, 1, 0},
            {1, 1, 0, 1, 1, 1, 0, 1, 0},
            {1, 1, 1, 0, 1, 1, 0, 1, 0},
            {1, 1, 1, 1, 1, 1, 0, 0, 1},
            {1, 1, 0, 0, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 0, 0, 1},
            {1, 1, 1, 1, 1, 0, 0, 1, 1},
            {1, 1, 0, 1, 1, 1, 0, 1, 1},
            {1, 1, 1, 0, 1, 1, 0, 1, 1},
            {1, 1, 1, 1, 1, 1, 0, 1, 0},
            {1, 1, 0, 1, 1, 1, 0, 1, 1},
            {1, 1, 1, 1, 1, 1, 0, 1, 0},
            {1, 1, 1, 1, 1, 0, 1, 1, 0},
            {1, 1, 0, 1, 1, 1, 1, 1, 0},
            {1, 1, 1, 0, 1, 1, 1, 1, 0},
            {1, 1, 1, 1, 1, 1, 0, 1, 1},
            {1, 1, 0, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 0, 1, 1},
            {1, 1, 1, 1, 1, 0, 1, 1, 1},
            {1, 1, 0, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 0, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 0, 0},
            {1, 1, 1, 0, 1, 1, 0, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 0, 0},
            {1, 1, 1, 1, 1, 1, 0, 1, 0},
            {1, 1, 1, 1, 1, 1, 0, 1, 0},
            {1, 1, 1, 1, 1, 1, 0, 1, 0},
            {1, 1, 1, 1, 1, 1, 1, 0, 1},
            {1, 1, 1, 0, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 0, 1},
            {1, 1, 1, 1, 1, 1, 0, 1, 1},
            {1, 1, 1, 1, 1, 1, 0, 1, 1},
            {1, 1, 1, 1, 1, 1, 0, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 0},
            {1, 1, 1, 1, 1, 1, 0, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 0},
            {1, 1, 1, 1, 1, 1, 1, 1, 0},
            {1, 1, 1, 1, 1, 1, 1, 1, 0},
            {1, 1, 1, 1, 1, 1, 1, 1, 0},
            {1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 1, 0, 1, 0, 0, 0, 1},
            {1, 0, 1, 0, 1, 0, 1, 0, 0},
            {1, 0, 0, 0, 1, 0, 1, 0, 1},
            {0, 0, 1, 0, 1, 0, 1, 0, 1},
            {1, 0, 1, 0, 1, 1, 0, 0, 1},
            {1, 0, 1, 0, 1, 0, 1, 1, 0},
            {1, 0, 0, 0, 1, 0, 1, 1, 1},
            {0, 0, 1, 0, 1, 0, 1, 1, 1},
            {1, 0, 1, 1, 1, 0, 0, 0, 1},
            {1, 0, 1, 1, 1, 0, 1, 0, 0},
            {1, 0, 0, 0, 1, 1, 1, 0, 1},
            {0, 0, 1, 0, 1, 1, 1, 0, 1},
            {1, 0, 1, 1, 1, 1, 0, 0, 1},
            {1, 0, 1, 1, 1, 0, 1, 1, 0},
            {1, 0, 0, 0, 1, 1, 1, 1, 1},
            {0, 0, 1, 0, 1, 1, 1, 1, 1},
            {1, 1, 1, 0, 1, 0, 0, 0, 1},
            {1, 1, 1, 0, 1, 0, 1, 0, 0},
            {1, 0, 0, 1, 1, 0, 1, 0, 1},
            {0, 1, 1, 0, 1, 0, 1, 0, 1},
            {1, 1, 1, 0, 1, 1, 0, 0, 1},
            {1, 1, 1, 0, 1, 0, 1, 1, 0},
            {1, 0, 0, 1, 1, 0, 1, 1, 1},
            {0, 1, 1, 0, 1, 0, 1, 1, 1},
            {1, 1, 1, 1, 1, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 0, 1, 0, 0},
            {1, 0, 0, 1, 1, 1, 1, 0, 1},
            {0, 1, 1, 0, 1, 1, 1, 0, 1},
            {1, 1, 1, 1, 1, 1, 0, 0, 1},
            {1, 1, 1, 1, 1, 0, 1, 1, 0},
            {1, 0, 0, 1, 1, 1, 1, 1, 1},
            {0, 1, 1, 0, 1, 1, 1, 1, 1},
            {1, 0, 1, 0, 1, 0, 0, 1, 0},
            {1, 0, 0, 0, 1, 1, 1, 0, 0},
            {0, 1, 0, 0, 1, 0, 1, 0, 1},
            {0, 0, 1, 1, 1, 0, 0, 0, 1},
            {1, 0, 1, 0, 1, 1, 0, 1, 0},
            {1, 0, 0, 0, 1, 1, 1, 1, 0},
            {0, 1, 0, 0, 1, 0, 1, 1, 1},
            {0, 0, 1, 1, 1, 0, 0, 1, 1},
            {1, 0, 1, 1, 1, 0, 0, 1, 0},
            {1, 0, 0, 1, 1, 1, 1, 0, 0},
            {0, 1, 0, 0, 1, 1, 1, 0, 1},
            {0, 0, 1, 1, 1, 1, 0, 0, 1},
            {1, 0, 1, 1, 1, 1, 0, 1, 0},
            {1, 0, 0, 1, 1, 1, 1, 1, 0},
            {0, 1, 0, 0, 1, 1, 1, 1, 1},
            {0, 0, 1, 1, 1, 1, 0, 1, 1},
            {1, 1, 1, 0, 1, 0, 0, 1, 0},
            {1, 1, 0, 0, 1, 1, 1, 0, 0},
            {0, 1, 0, 1, 1, 0, 1, 0, 1},
            {0, 1, 1, 1, 1, 0, 0, 0, 1},
            {1, 1, 1, 0, 1, 1, 0, 1, 0},
            {1, 1, 0, 0, 1, 1, 1, 1, 0},
            {0, 1, 0, 1, 1, 0, 1, 1, 1},
            {0, 1, 1, 1, 1, 0, 0, 1, 1},
            {1, 1, 1, 1, 1, 0, 0, 1, 0},
            {1, 1, 0, 1, 1, 1, 1, 0, 0},
            {0, 1, 0, 1, 1, 1, 1, 0, 1},
            {0, 1, 1, 1, 1, 1, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 0, 1, 0},
            {1, 1, 0, 1, 1, 1, 1, 1, 0},
            {0, 1, 0, 1, 1, 1, 1, 1, 1},
            {0, 1, 1, 1, 1, 1, 0, 1, 1},
            {1, 0, 1, 0, 1, 0, 0, 1, 1},
            {1, 0, 1, 0, 1, 1, 1, 0, 0},
            {1, 1, 0, 0, 1, 0, 1, 0, 1},
            {0, 0, 1, 1, 1, 0, 1, 0, 1},
            {1, 0, 1, 0, 1, 1, 0, 1, 1},
            {1, 0, 1, 0, 1, 1, 1, 1, 0},
            {1, 1, 0, 0, 1, 0, 1, 1, 1},
            {0, 0, 1, 1, 1, 0, 1, 1, 1},
            {1, 0, 1, 1, 1, 0, 0, 1, 1},
            {1, 0, 1, 1, 1, 1, 1, 0, 0},
            {1, 1, 0, 0, 1, 1, 1, 0, 1},
            {0, 0, 1, 1, 1, 1, 1, 0, 1},
            {1, 0, 1, 1, 1, 1, 0, 1, 1},
            {1, 0, 1, 1, 1, 1, 1, 1, 0},
            {1, 1, 0, 0, 1, 1, 1, 1, 1},
            {0, 0, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 0, 1, 0, 0, 1, 1},
            {1, 1, 1, 0, 1, 1, 1, 0, 0},
            {1, 1, 0, 1, 1, 0, 1, 0, 1},
            {0, 1, 1, 1, 1, 0, 1, 0, 1},
            {1, 1, 1, 0, 1, 1, 0, 1, 1},
            {1, 1, 1, 0, 1, 1, 1, 1, 0},
            {1, 1, 0, 1, 1, 0, 1, 1, 1},
            {0, 1, 1, 1, 1, 0, 1, 1, 1},
            {1, 1, 1, 1, 1, 0, 0, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 0, 0},
            {1, 1, 0, 1, 1, 1, 1, 0, 1},
            {0, 1, 1, 1, 1, 1, 1, 0, 1},
            {1, 1, 1, 1, 1, 1, 0, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 0},
            {1, 1, 0, 1, 1, 1, 1, 1, 1},
            {0, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 1, 0, 1, 0, 1, 0, 0},
            {1, 0, 0, 0, 1, 0, 1, 0, 1},
            {0, 0, 1, 0, 1, 0, 1, 0, 1},
            {1, 0, 1, 0, 1, 0, 0, 0, 1},
            {1, 0, 1, 0, 1, 1, 1, 0, 0},
            {1, 0, 0, 0, 1, 0, 1, 1, 1},
            {0, 0, 1, 0, 1, 0, 1, 1, 1},
            {1, 0, 1, 0, 1, 0, 0, 1, 1},
            {1, 0, 1, 1, 1, 0, 1, 0, 0},
            {1, 0, 0, 1, 1, 0, 1, 0, 1},
            {0, 0, 1, 0, 1, 1, 1, 0, 1},
            {1, 0, 1, 0, 1, 1, 0, 0, 1},
            {1, 0, 1, 1, 1, 1, 1, 0, 0},
            {1, 0, 0, 1, 1, 0, 1, 1, 1},
            {0, 0, 1, 0, 1, 1, 1, 1, 1},
            {1, 0, 1, 0, 1, 1, 0, 1, 1},
            {1, 1, 1, 0, 1, 0, 1, 0, 0},
            {1, 1, 0, 0, 1, 0, 1, 0, 1},
            {0, 0, 1, 1, 1, 0, 1, 0, 1},
            {1, 1, 1, 0, 1, 0, 0, 0, 1},
            {1, 1, 1, 0, 1, 1, 1, 0, 0},
            {1, 1, 0, 0, 1, 0, 1, 1, 1},
            {0, 0, 1, 1, 1, 0, 1, 1, 1},
            {1, 1, 1, 0, 1, 0, 0, 1, 1},
            {1, 1, 1, 1, 1, 0, 1, 0, 0},
            {1, 1, 0, 1, 1, 0, 1, 0, 1},
            {0, 0, 1, 1, 1, 1, 1, 0, 1},
            {1, 1, 1, 0, 1, 1, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 0, 0},
            {1, 1, 0, 1, 1, 0, 1, 1, 1},
            {0, 0, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 0, 1, 1, 0, 1, 1},
            {1, 0, 1, 0, 1, 0, 1, 0, 1},
            {1, 0, 1, 0, 1, 0, 1, 0, 1},
            {1, 0, 1, 0, 1, 0, 1, 0, 1},
            {1, 0, 1, 0, 1, 0, 1, 0, 1},
            {1, 0, 1, 0, 1, 1, 1, 0, 1},
            {1, 0, 1, 0, 1, 0, 1, 1, 1},
            {1, 0, 1, 0, 1, 0, 1, 1, 1},
            {1, 0, 1, 0, 1, 0, 1, 1, 1},
            {1, 0, 1, 1, 1, 0, 1, 0, 1},
            {1, 0, 1, 1, 1, 0, 1, 0, 1},
            {1, 0, 1, 0, 1, 1, 1, 0, 1},
            {1, 0, 1, 0, 1, 1, 1, 0, 1},
            {1, 0, 1, 1, 1, 1, 1, 0, 1},
            {1, 0, 1, 1, 1, 0, 1, 1, 1},
            {1, 0, 1, 0, 1, 1, 1, 1, 1},
            {1, 0, 1, 0, 1, 1, 1, 1, 1},
            {1, 1, 1, 0, 1, 0, 1, 0, 1},
            {1, 1, 1, 0, 1, 0, 1, 0, 1},
            {1, 0, 1, 1, 1, 0, 1, 0, 1},
            {1, 1, 1, 0, 1, 0, 1, 0, 1},
            {1, 1, 1, 0, 1, 1, 1, 0, 1},
            {1, 1, 1, 0, 1, 0, 1, 1, 1},
            {1, 0, 1, 1, 1, 0, 1, 1, 1},
            {1, 1, 1, 0, 1, 0, 1, 1, 1},
            {1, 1, 1, 1, 1, 0, 1, 0, 1},
            {1, 1, 1, 1, 1, 0, 1, 0, 1},
            {1, 0, 1, 1, 1, 1, 1, 0, 1},
            {1, 1, 1, 0, 1, 1, 1, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 0, 1},
            {1, 1, 1, 1, 1, 0, 1, 1, 1},
            {1, 0, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 0, 1, 1, 1, 1, 1},
            {1, 0, 1, 0, 1, 0, 1, 1, 0},
            {1, 0, 0, 0, 1, 1, 1, 0, 1},
            {0, 1, 1, 0, 1, 0, 1, 0, 1},
            {1, 0, 1, 1, 1, 0, 0, 0, 1},
            {1, 0, 1, 0, 1, 1, 1, 1, 0},
            {1, 0, 0, 0, 1, 1, 1, 1, 1},
            {0, 1, 1, 0, 1, 0, 1, 1, 1},
            {1, 0, 1, 1, 1, 0, 0, 1, 1},
            {1, 0, 1, 1, 1, 0, 1, 1, 0},
            {1, 0, 0, 1, 1, 1, 1, 0, 1},
            {0, 1, 1, 0, 1, 1, 1, 0, 1},
            {1, 0, 1, 1, 1, 1, 0, 0, 1},
            {1, 0, 1, 1, 1, 1, 1, 1, 0},
            {1, 0, 0, 1, 1, 1, 1, 1, 1},
            {0, 1, 1, 0, 1, 1, 1, 1, 1},
            {1, 0, 1, 1, 1, 1, 0, 1, 1},
            {1, 1, 1, 0, 1, 0, 1, 1, 0},
            {1, 1, 0, 0, 1, 1, 1, 0, 1},
            {0, 1, 1, 1, 1, 0, 1, 0, 1},
            {1, 1, 1, 1, 1, 0, 0, 0, 1},
            {1, 1, 1, 0, 1, 1, 1, 1, 0},
            {1, 1, 0, 0, 1, 1, 1, 1, 1},
            {0, 1, 1, 1, 1, 0, 1, 1, 1},
            {1, 1, 1, 1, 1, 0, 0, 1, 1},
            {1, 1, 1, 1, 1, 0, 1, 1, 0},
            {1, 1, 0, 1, 1, 1, 1, 0, 1},
            {0, 1, 1, 1, 1, 1, 1, 0, 1},
            {1, 1, 1, 1, 1, 1, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 0},
            {1, 1, 0, 1, 1, 1, 1, 1, 1},
            {0, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 0, 1, 1},
            {1, 0, 1, 0, 1, 0, 1, 1, 1},
            {1, 0, 1, 0, 1, 1, 1, 0, 1},
            {1, 1, 1, 0, 1, 0, 1, 0, 1},
            {1, 0, 1, 1, 1, 0, 1, 0, 1},
            {1, 0, 1, 0, 1, 1, 1, 1, 1},
            {1, 0, 1, 0, 1, 1, 1, 1, 1},
            {1, 1, 1, 0, 1, 0, 1, 1, 1},
            {1, 0, 1, 1, 1, 0, 1, 1, 1},
            {1, 0, 1, 1, 1, 0, 1, 1, 1},
            {1, 0, 1, 1, 1, 1, 1, 0, 1},
            {1, 1, 1, 0, 1, 1, 1, 0, 1},
            {1, 0, 1, 1, 1, 1, 1, 0, 1},
            {1, 0, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 0, 1, 1, 1, 1, 1},
            {1, 0, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 0, 1, 0, 1, 1, 1},
            {1, 1, 1, 0, 1, 1, 1, 0, 1},
            {1, 1, 1, 1, 1, 0, 1, 0, 1},
            {1, 1, 1, 1, 1, 0, 1, 0, 1},
            {1, 1, 1, 0, 1, 1, 1, 1, 1},
            {1, 1, 1, 0, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 0, 1, 1, 1},
            {1, 1, 1, 1, 1, 0, 1, 1, 1},
            {1, 1, 1, 1, 1, 0, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1}
        };

    for(int i=0;i<markPatterns.size();i++)
    {
        if(pattern == markPatterns[i]) {
            return true;
        }
    }
    return false;
}

vector<vector<unsigned char>> GetSkeletonizedImage(vector< vector<unsigned char> > Imagedata,  int height, int width)
{
    bool flag = true;

    vector<vector<unsigned char>> OutputImage(height, vector<unsigned char> (width, 0));    

    copy(Imagedata.begin(),Imagedata.end(), OutputImage.begin()); 

    vector<vector<unsigned char>> ExtendedImage(height+2, vector<unsigned char> (width+2, 0));
    
    vector<vector<unsigned char>> MidImage(height, vector<unsigned char> (width, 0));
    
    vector<vector<unsigned char>> ExtendedMidImage(height+2, vector<unsigned char> (width+2, 0));

    vector<vector<unsigned char>> finalImage(height, vector<unsigned char> (width, 0));

    vector<unsigned char> pattern_conditional, pattern_unconditional;

    int iter = 0;
    while(flag)
    {   
        cout<<"iteration:"<<iter<<endl;
        ExtendedImage = extendImage(OutputImage, height, width);
        
        for(int i=1;i<height+1;i++)
        {
            for(int j=1;j<width+1;j++)
            {
                    if (ExtendedImage[i][j] == 1)
                    {
                        pattern_conditional.clear();
                        for(int m=-1; m<=1; m++)
                        {
                            for(int n=-1; n<=1; n++)
                            { 
                                pattern_conditional.push_back(ExtendedImage[i+m][j+n]);
                            }
                        } 
                        bool hit = ApplyCondMark(pattern_conditional);
                        if(hit){
                            MidImage[i-1][j-1] = 1;
                        }
                        else
                            MidImage[i-1][j-1] = 0;
                    } else {
                        MidImage[i-1][j-1] = ExtendedImage[i][j];
                    }
            }
        }

        //  cout << "hey" << endl;

        ExtendedMidImage = extendImage(MidImage, height, width);
        //  cout << "hey" << endl;
        
        
        for(int i=1;i<height+1;i++)
        {
            for(int j=1; j<width+1; j++)
            {
                if(ExtendedMidImage[i][j]==1)
                {
                    pattern_unconditional.clear();
                    for(int m=-1; m<=1; m++)
                    {
                        for(int n=-1; n<=1; n++)
                        { 
                            pattern_unconditional.push_back(ExtendedMidImage[i+m][j+n]);
                        }
                    }

                    bool hit = ApplyUncondMark(pattern_unconditional);
                    if(hit){
                        finalImage[i-1][j-1] = 1;
                    }
                    else
                        finalImage[i-1][j-1] = 0;
                } else {
                    finalImage[i-1][j-1] = ExtendedMidImage[i][j];
                }
            }
        }

        for(int i=1;i<height+1;i++)
        {
            for(int j=1; j<width+1; j++)
            {
                OutputImage[i-1][j-1] = ExtendedImage[i][j] && ((!ExtendedMidImage[i][j]) || finalImage[i-1][j-1]);
            }
        }

        int pixel_count = 0;
        for(int i=1;i<height+1;i++)
        {
            for(int j=1; j<width+1; j++)
            {
                if (ExtendedImage[i][j] == OutputImage[i-1][j-1]){
                    pixel_count +=1;
                }
            
            }
        }

        if(pixel_count == height*width){
            flag = false;
            cout<<"final iterations:" << iter << endl;
        }
        iter+=1;
    }
    return OutputImage;
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

    vector<vector<unsigned char>> SkelotonizedImage(height, vector<unsigned char> (width, 0));

    SkelotonizedImage = GetSkeletonizedImage(BinaryImage, height, width);

    vector<vector<unsigned char>> extendSktImage(height+2, vector<unsigned char> (width+2, 0));    
    extendSktImage = extendImage(SkelotonizedImage, height, width);
    
    unsigned char x,x0,x1,x2,x3,x4,x5,x6,x7,L1,L2,L3,L4,PQ,P1,P2,P3,P4,P5,P6;

    //bridging
    for(int i=1;i<height+1;i++)
    {
        for(int j=1; j<width+1; j++)
        {
            x = extendSktImage[i][j];  
            x0 = extendSktImage[i][j+1];
            x1 = extendSktImage[i-1][j+1];
            x2 = extendSktImage[i-1][j];
            x3 = extendSktImage[i-1][j-1];
            x4 = extendSktImage[i][j-1];
            x5 = extendSktImage[i+1][j-1];
            x6 = extendSktImage[i+1][j];
            x7 = extendSktImage[i+1][j+1];  

            L1 = !x and !x0 and x1 and !x2 and x3 and !x4 and !x5 and !x6 and !x7;
            L2 = !x and !x0 and !x1 and !x2 and x3 and !x4 and x5 and !x6 and !x7;
            L3 = !x and !x0 and !x1 and !x2 and !x3 and !x4 and x5 and !x6 and x7;
            L4 = !x and !x0 and x1 and !x2 and !x3 and !x4 and !x5 and !x6 and x7;

            PQ = L1 or L2 or L3 or L4;

            P1 = !x2 and !x6 and (x3 or x4 or x5 ) and (x0 or x1 or x7) and !PQ;
            P2 = !x0 and !x4 and (x1 or x2 or x3 ) and (x5 or x6 or x7) and !PQ;

            P3 = !x0 and !x6 and x7 and (x2 or x3 or x4);
            P4 = !x0 and !x2 and x1 and (x4 or x5 or x6);
            P5 = !x2 and !x4 and x3 and (x0 or x6 or x7);
            P6 = !x4 and !x6 and x5 and (x0 or x1 or x2);

            extendSktImage[i][j] = (x or (P1 or P2 or P3 or P4 or P5 or P6));

        }
    }

    unsigned char OutputSkelotonizedImage[height][width];
    for(int i=0;i<height;i++)
    {
        for(int j=0; j<width; j++)
        {
            if (extendSktImage[i][j] == 1) 
                OutputSkelotonizedImage[i][j] = 255;
            else
            {
                OutputSkelotonizedImage[i][j] = 0;
            }
            
        }
    }
    
    // Write image data (filename specified by second argument) from image data matrix
    if (!(imagefile = fopen(argv[2], "wb")))
    {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(OutputSkelotonizedImage, sizeof(unsigned char), width * height, imagefile);
    fclose(imagefile);

    return 0;

}