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
            {1, 1, 0, 0, 1, 1, 0, 0, 0},
            {0, 1, 0, 0, 1, 1, 0, 0, 1},
            {0, 1, 1, 1, 1, 0, 0, 0, 0},
            {0, 0, 1, 0, 1, 1, 0, 1, 0},
            {0, 1, 1, 0, 1, 1, 0, 0, 0},
            {1, 1, 0, 1, 1, 0, 0, 0, 0},
            {0, 0, 0, 1, 1, 0, 1, 1, 0},
            {0, 0, 0, 0, 1, 1, 0, 1, 1},
            {1, 1, 0, 0, 1, 1, 0, 0, 1},
            {0, 1, 1, 1, 1, 0, 1, 0, 0},
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
            {1, 0, 1, 1, 1, 1, 1, 1, 1}

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
        {0, 0, 1, 0, 1, 0, 0, 0, 0},
        {1, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 1, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 1, 0, 1, 1, 0, 0, 0},
        {0, 1, 1, 0, 1, 0, 0, 0, 0},
        {1, 1, 0, 0, 1, 0, 0, 0, 0},
        {1, 0, 0, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 1, 1, 0},
        {0, 0, 0, 0, 1, 0, 0, 1, 1},
        {0, 0, 0, 0, 1, 1, 0, 0, 1},
        {0, 1, 1, 1, 1, 0, 0, 0, 0},
        {1, 1, 0, 0, 1, 1, 0, 0, 0},
        {0, 1, 0, 0, 1, 1, 0, 0, 1},
        {0, 0, 1, 0, 1, 1, 0, 1, 0},
        {0, 0, 1, 0, 1, 1, 1, 0, 0},
        {1, 1, 0, 0, 1, 0, 0, 0, 1},
        {0, 0, 1, 0, 1, 0, 1, 1, 0},
        {1, 0, 0, 0, 1, 1, 0, 0, 1},
        {0, 1, 1, 0, 1, 0, 1, 0, 0},
        {1, 0, 0, 1, 1, 0, 0, 0, 1},
        {0, 0, 1, 1, 1, 0, 1, 0, 0},
        {1, 0, 0, 0, 1, 0, 0, 1, 1},
        {0, 1, 1, 0, 1, 1, 1, 0, 0},
        {1, 1, 0, 1, 1, 0, 0, 0, 1},
        {0, 0, 1, 1, 1, 0, 1, 1, 0},
        {1, 0, 0, 0, 1, 1, 0, 1, 1},
        {0, 1, 0, 1, 1, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 1, 0},
        {0, 0, 0, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 1, 1, 0, 0, 1, 0},
        {0, 1, 0, 1, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 1, 1, 0, 1, 0},
        {0, 1, 0, 0, 1, 1, 0, 1, 0},
        {0, 1, 0, 0, 1, 1, 1, 0, 0},
        {0, 1, 0, 1, 1, 0, 0, 0, 1},
        {0, 0, 1, 1, 1, 0, 0, 1, 0},
        {1, 0, 0, 0, 1, 1, 0, 1, 0},
        {1, 1, 0, 1, 1, 0, 0, 0, 0},
        {1, 1, 0, 1, 1, 0, 0, 0, 1},
        {1, 1, 0, 1, 1, 0, 0, 1, 0},
        {1, 1, 0, 1, 1, 0, 0, 1, 1},
        {1, 1, 0, 1, 1, 0, 1, 0, 0},
        {1, 1, 0, 1, 1, 0, 1, 0, 1},
        {1, 1, 0, 1, 1, 0, 1, 1, 0},
        {1, 1, 0, 1, 1, 0, 1, 1, 1},
        {0, 1, 0, 1, 1, 1, 1, 0, 0},
        {0, 1, 0, 1, 1, 1, 0, 0, 1},
        {0, 0, 0, 1, 1, 1, 0, 1, 1},
        {0, 0, 0, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 0, 0, 1, 0},
        {0, 1, 0, 1, 1, 0, 0, 1, 1},
        {0, 1, 0, 0, 1, 1, 0, 1, 1},
        {0, 1, 1, 0, 1, 1, 0, 1, 0},
        {0, 1, 0, 0, 1, 1, 1, 0, 1},
        {0, 1, 0, 1, 1, 0, 1, 0, 1},
        {0, 0, 1, 1, 1, 0, 0, 1, 1},
        {1, 0, 0, 0, 1, 1, 1, 1, 0},
        {1, 1, 0, 1, 1, 1, 0, 0, 0},
        {1, 1, 0, 1, 1, 1, 0, 0, 1},
        {1, 1, 0, 1, 1, 1, 0, 1, 0},
        {1, 1, 0, 1, 1, 1, 0, 1, 1},
        {1, 1, 0, 1, 1, 1, 1, 0, 0},
        {1, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 1, 0, 1, 1, 1, 1, 1, 0},
        {1, 1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 1, 1, 1, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 0, 1, 0},
        {1, 0, 0, 1, 1, 1, 0, 1, 0},
        {1, 1, 0, 1, 1, 0, 0, 1, 0},
        {0, 1, 0, 1, 1, 0, 1, 1, 0},
        {0, 1, 0, 0, 1, 1, 1, 1, 0},
        {1, 1, 0, 0, 1, 1, 0, 1, 0},
        {1, 1, 0, 0, 1, 1, 1, 0, 0},
        {0, 1, 1, 1, 1, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 0, 1, 0},
        {1, 0, 1, 0, 1, 1, 0, 1, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 0, 0, 1, 0},
        {1, 1, 1, 1, 1, 0, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 0, 0},
        {1, 1, 1, 1, 1, 0, 1, 0, 1},
        {1, 1, 1, 1, 1, 0, 1, 1, 0},
        {1, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 0, 1, 1, 1, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 0, 0, 1},
        {0, 0, 1, 1, 1, 1, 0, 1, 1},
        {1, 0, 0, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 0, 0, 1, 0},
        {0, 1, 0, 1, 1, 0, 1, 1, 1},
        {0, 1, 0, 0, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 0, 1, 0},
        {1, 1, 0, 0, 1, 1, 1, 0, 1},
        {0, 1, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 1, 1, 1, 0, 0, 1, 1},
        {1, 0, 1, 0, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 0, 1, 0},
        {1, 1, 1, 1, 1, 1, 0, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 0},
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

vector<vector<unsigned char> > GetThinnedImage(vector< vector<unsigned char> > Imagedata,  int height, int width)
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

        ExtendedMidImage = extendImage(MidImage, height, width);        
        
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

    vector<vector<unsigned char>> ThinnedImage(height, vector<unsigned char> (width, 0));

    ThinnedImage = GetThinnedImage(BinaryImage, height, width);

    unsigned char OutputThinnedImage[height][width];
    for(int i=0;i<height;i++)
    {
        for(int j=0; j<width; j++)
        {
            if (ThinnedImage[i][j] == 1) 
                OutputThinnedImage[i][j] = 255;
            else
            {
                OutputThinnedImage[i][j] = 0;
            }
            
        }
    }
    
    // Write image data (filename specified by second argument) from image data matrix
    if (!(imagefile = fopen(argv[2], "wb")))
    {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(OutputThinnedImage, sizeof(unsigned char), width * height, imagefile);
    fclose(imagefile);

    return 0;

}