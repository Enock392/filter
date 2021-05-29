#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            int addition=image[i][j].rgbtRed+image[i][j].rgbtGreen+image[i][j].rgbtBlue;
            int average=(int)round(addition/3.0);
            image[i][j].rgbtRed=average;
            image[i][j].rgbtGreen=average;
            image[i][j].rgbtBlue=average;
        }
    }

    return;
}
//cap at 255
int cap(int RGBvalue){
    if(RGBvalue>255){
        RGBvalue = 255;
    }
    return RGBvalue;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            int originalRed=image[i][j].rgbtRed;
            int originalGreen=image[i][j].rgbtGreen;
            int originalBlue=image[i][j].rgbtBlue;
            int red = cap(round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue));
            int green = cap(round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue));
            int blue = cap(round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue));
            image[i][j].rgbtRed= red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int thiswidth,red,blue,green;
    if(width % 2==0){
        thiswidth=width/2;
    }else{
        thiswidth=(int)floor(width/2);
    }
        for(int i = 0 ; i < height ; i++ ){
            for( int j = 0 ;j < thiswidth ;j++){
                red=image[i][j].rgbtRed;
                green=image[i][j].rgbtGreen;
                blue=image[i][j].rgbtBlue;
                image[i][j].rgbtRed=image[i][width-j-1].rgbtRed;
                image[i][j].rgbtGreen=image[i][width-j-1].rgbtGreen;
                image[i][j].rgbtBlue=image[i][width-j-1].rgbtBlue;
                image[i][width-j-1].rgbtRed=red;
                image[i][width-j-1].rgbtGreen=green;
                image[i][width-j-1].rgbtBlue=blue;
            }

        }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float Red,Green,Blue;
    RGBTRIPLE tempimage[height][width];
    

    for(int i = 0 ;i< height ; i++ ){
        for(int j =0 ; j< width ;j++){
            Red=Green=Blue=0;
            int k_start=-1;
            int m_start=-1;
            int k_end=2;
            int m_end=2;
            int counter=0;
            if(i==0){
                k_start=0;
            }
            if(j==0 ){
                m_start=0;
            }
            if(j == width-1){
                m_end=1;
            }
            if(i == height-1){
                k_end=1;
            }
            for(int k = k_start ;k < k_end ;k++){
                for (int m = m_start ;m < m_end; m++){
                    Red+=image[k+i][m+j].rgbtRed;
                    Green+=image[k+i][m+j].rgbtGreen;
                    Blue+=image[k+i][m+j].rgbtBlue;
                    counter++;
                    
                }
            }
            tempimage[i][j].rgbtRed=(int)round(Red/counter);
            tempimage[i][j].rgbtGreen=(int)round(Green/counter);
            tempimage[i][j].rgbtBlue=(int)round(Blue/counter);
        }
    }
    for(int i =0 ; i < height ;i++){
        for (int j =0 ; j < width ; j++){
            image[i][j].rgbtRed=tempimage[i][j].rgbtRed;
            image[i][j].rgbtGreen=tempimage[i][j].rgbtGreen;
            image[i][j].rgbtBlue=tempimage[i][j].rgbtBlue;
        }
    }
    return;
}
