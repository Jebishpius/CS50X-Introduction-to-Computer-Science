#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
       {
          float avg1 = round((image[i][j].rgbtRed+ image[i][j].rgbtBlue + image[i][j].rgbtGreen)/3.0f);

           image[i][j].rgbtRed = avg1;
           image[i][j].rgbtBlue = avg1;
           image[i][j].rgbtGreen = avg1;
       }

    }

    return;
}

// Convert image to sepia
void sepia (int height, int width, RGBTRIPLE image[height][width])
{
    float sr, sb, sg;
    for (int i = 0; i <= height - 1; i++)
    {
        for (int j = 0; j <= width - 1; j++)
        {
          sr = round (.393 * image[i][j].rgbtRed + .189 * image[i][j].rgbtBlue + .769 * image[i][j].rgbtGreen);
          sb = round (.272 * image[i][j].rgbtRed + .131 * image[i][j].rgbtBlue + .534 * image[i][j].rgbtGreen);
          sg = round (.349 * image[i][j].rgbtRed + .168 * image[i][j].rgbtBlue + .686 * image[i][j].rgbtGreen);
          if (sr > 255)
          {
              sr = 255;
          }
          if (sb > 255)
         {
             sb = 255;
         }
          if (sg > 255)
          {
              sg = 255;
          }
          image[i][j].rgbtRed = round (sr);
          image[i][j].rgbtBlue = round (sb);
          image[i][j].rgbtGreen = round (sg);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int r,b,g;
      printf("Height: %i Width: %i\n", height, width);
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width/2; j++)
        {
          r = image[i][j].rgbtRed;
          b = image[i][j].rgbtBlue;
          g = image[i][j].rgbtGreen;
          image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed ;
          image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
          image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
          image[i][width - j - 1].rgbtRed = r;
          image[i][width - j - 1].rgbtBlue = b;
          image[i][width - j - 1].rgbtGreen = g;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
  RGBTRIPLE imagea[height][width];
    for (int n = 0; n <= height - 1; n++)
    {
        for (int m = 0; m <= width - 1; m++)
        {
            imagea[n][m] = image[n][m];


        }
    }



    for(int i = 0; i <= height-1; i++)
    {
        for(int j = 0; j <= width-1; j++)
        {



            // Corner 1
            if(i==0  &&  j == 0 ){
                float tmpred = (imagea[i][j].rgbtRed + imagea[i][j+1].rgbtRed + imagea[i+1][j].rgbtRed + imagea[i+1][j+1].rgbtRed)/4.0f;
                float tmpgreen = (imagea[i][j].rgbtGreen + imagea[i][j+1].rgbtGreen + imagea[i+1][j].rgbtGreen + imagea[i+1][j+1].rgbtGreen)/4.0f;
               float tmpblue = (imagea[i][j].rgbtBlue + imagea[i][j+1].rgbtBlue + imagea[i+1][j].rgbtBlue + imagea[i+1][j+1].rgbtBlue)/4.0f;

               image[i][j].rgbtRed =  round(tmpred);
           image[i][j].rgbtBlue =  round(tmpblue);
           image[i][j].rgbtGreen = round(tmpgreen);




            }
            // Corner 2
            else if(i==(height-1) && j == 0){
                float tmpred = (imagea[i][j].rgbtRed + imagea[i][j+1].rgbtRed + imagea[i-1][j].rgbtRed + imagea[i-1][j+1].rgbtRed)/4.0f;
                float tmpgreen = (imagea[i][j].rgbtGreen + imagea[i][j+1].rgbtGreen + imagea[i-1][j].rgbtGreen + imagea[i-1][j+1].rgbtGreen)/4.0f;
              float tmpblue = (imagea[i][j].rgbtBlue + imagea[i][j+1].rgbtBlue + imagea[i-1][j].rgbtBlue + imagea[i-1][j+1].rgbtBlue)/4.0f;

               image[i][j].rgbtRed =  round(tmpred);
           image[i][j].rgbtBlue =  round(tmpblue);
           image[i][j].rgbtGreen = round(tmpgreen);

            }
            // Corner 3
            else if (i ==0 && j == (width-1)){
                float tmpred = (imagea[i][j].rgbtRed + imagea[i][j-1].rgbtRed + imagea[i+1][j].rgbtRed + imagea[i+1][j-1].rgbtRed)/4.0f;
                float tmpgreen = (imagea[i][j].rgbtGreen + imagea[i][j-1].rgbtGreen + imagea[i+1][j].rgbtGreen + imagea[i+1][j-1].rgbtGreen)/4.0f;
               float tmpblue = (imagea[i][j].rgbtBlue + imagea[i][j-1].rgbtBlue + imagea[i+1][j].rgbtBlue + imagea[i+1][j-1].rgbtBlue)/4.0f;

               image[i][j].rgbtRed =  round(tmpred);
           image[i][j].rgbtBlue =  round(tmpblue);
           image[i][j].rgbtGreen = round(tmpgreen);


            }
            // Corner 4
            else if (i == (height-1) && j == (width-1)) {
                float tmpred = (imagea[i][j].rgbtRed + imagea[i][j-1].rgbtRed + imagea[i-1][j].rgbtRed + imagea[i-1][j-1].rgbtRed)/4.0f;
                float tmpgreen = (imagea[i][j].rgbtGreen + imagea[i][j-1].rgbtGreen + imagea[i-1][j].rgbtGreen + imagea[i-1][j-1].rgbtGreen)/4.0f;
                float tmpblue = (imagea[i][j].rgbtBlue + imagea[i][j-1].rgbtBlue + imagea[i-1][j].rgbtBlue + imagea[i-1][j-1].rgbtBlue)/4.0f;

               image[i][j].rgbtRed =  round(tmpred);
           image[i][j].rgbtBlue =  round(tmpblue);
           image[i][j].rgbtGreen = round(tmpgreen);
            }
            // west face edges
            else if(i > 0 && i < (height-1) && j == 0){
                int tmpred = round((imagea[i][j].rgbtRed + imagea[i-1][j].rgbtRed + imagea[i-1][j+1].rgbtRed + imagea[i][j+1].rgbtRed +imagea[i+1][j+1].rgbtRed+imagea[i+1][j].rgbtRed)/6.0f);
                int tmpgreen = round((imagea[i][j].rgbtGreen + imagea[i-1][j].rgbtGreen + imagea[i-1][j+1].rgbtGreen + imagea[i][j+1].rgbtGreen+imagea[i+1][j+1].rgbtGreen+imagea[i+1][j].rgbtGreen)/6.0f);
                int tmpblue = round((imagea[i][j].rgbtBlue + imagea[i-1][j].rgbtBlue + imagea[i-1][j+1].rgbtBlue + imagea[i][j+1].rgbtBlue+imagea[i+1][j+1].rgbtBlue+imagea[i+1][j].rgbtBlue)/6.0f);

               image[i][j].rgbtRed =  tmpred;
           image[i][j].rgbtBlue =  tmpblue;
           image[i][j].rgbtGreen = tmpgreen;
            }
            // east face edges
            else if(i > 0 && i < (height-1)  && j == (width-1)){
                int tmpred = round((imagea[i][j].rgbtRed + imagea[i-1][j].rgbtRed + imagea[i-1][j-1].rgbtRed + imagea[i][j-1].rgbtRed +imagea[i+1][j-1].rgbtRed+imagea[i+1][j].rgbtRed)/6.0f);
                int tmpgreen = round((imagea[i][j].rgbtGreen + imagea[i-1][j].rgbtGreen + imagea[i-1][j-1].rgbtGreen + imagea[i][j-1].rgbtGreen+imagea[i+1][j-1].rgbtGreen+imagea[i+1][j].rgbtGreen)/6.0f);
                int tmpblue = round((imagea[i][j].rgbtBlue + imagea[i-1][j].rgbtBlue + imagea[i-1][j-1].rgbtBlue + imagea[i][j-1].rgbtBlue+imagea[i+1][j-1].rgbtBlue+imagea[i+1][j].rgbtBlue)/6.0f);

               image[i][j].rgbtRed =  tmpred;
           image[i][j].rgbtBlue =  tmpblue;
           image[i][j].rgbtGreen = tmpgreen;
            }
            // north face edges
            else if(i ==0 && j > 0 && j < (width-1)){
                int tmpred = round((imagea[i][j].rgbtRed + imagea[i][j-1].rgbtRed + imagea[i+1][j-1].rgbtRed + imagea[i+1][j].rgbtRed +imagea[i+1][j+1].rgbtRed+imagea[i][j+1].rgbtRed)/6.0f);
                int tmpgreen = round((imagea[i][j].rgbtGreen + imagea[i][j-1].rgbtGreen + imagea[i+1][j-1].rgbtGreen + imagea[i+1][j].rgbtGreen+imagea[i+1][j+1].rgbtGreen+imagea[i][j+1].rgbtGreen)/6.0f);
                int tmpblue = round((imagea[i][j].rgbtBlue + imagea[i][j-1].rgbtBlue + imagea[i+1][j-1].rgbtBlue + imagea[i+1][j].rgbtBlue+imagea[i+1][j+1].rgbtBlue+imagea[i][j+1].rgbtBlue)/6.0f);

               image[i][j].rgbtRed =  tmpred;
           image[i][j].rgbtBlue =  tmpblue;
           image[i][j].rgbtGreen = tmpgreen;

            }
            // south face edges
            else if (i == (height-1) && j > 0 && j < (width-1)){
                int tmpred = round((imagea[i][j].rgbtRed + imagea[i][j-1].rgbtRed + imagea[i-1][j-1].rgbtRed + imagea[i-1][j].rgbtRed +imagea[i-1][j+1].rgbtRed+imagea[i][j+1].rgbtRed)/6.0f);
                int tmpgreen = round((imagea[i][j].rgbtGreen + imagea[i][j-1].rgbtGreen + imagea[i-1][j-1].rgbtGreen + imagea[i-1][j].rgbtGreen+imagea[i-1][j+1].rgbtGreen+imagea[i][j+1].rgbtGreen)/6.0f);
                int tmpblue = round((imagea[i][j].rgbtBlue + imagea[i][j-1].rgbtBlue + imagea[i-1][j-1].rgbtBlue + imagea[i-1][j].rgbtBlue+imagea[i-1][j+1].rgbtBlue+imagea[i][j+1].rgbtBlue)/6.0f);

               image[i][j].rgbtRed =  tmpred;
           image[i][j].rgbtBlue =  tmpblue;
           image[i][j].rgbtGreen = tmpgreen;

            }

            else {
                int tmpred = round((imagea[i][j].rgbtRed + imagea[i-1][j-1].rgbtRed + imagea[i-1][j].rgbtRed + imagea[i-1][j+1].rgbtRed +imagea[i][j+1].rgbtRed+imagea[i+1][j+1].rgbtRed+imagea[i+1][j].rgbtRed+imagea[i+1][j-1].rgbtRed+imagea[i][j-1].rgbtRed)/9.0f);
                int tmpgreen = round((imagea[i][j].rgbtGreen + imagea[i-1][j-1].rgbtGreen + imagea[i-1][j].rgbtGreen + imagea[i-1][j+1].rgbtGreen+imagea[i][j+1].rgbtGreen+imagea[i+1][j+1].rgbtGreen+imagea[i+1][j].rgbtGreen+imagea[i+1][j-1].rgbtGreen +imagea[i][j-1].rgbtGreen)/9.0f) ;
                int tmpblue = round((imagea[i][j].rgbtBlue + imagea[i-1][j-1].rgbtBlue + imagea[i-1][j].rgbtBlue + imagea[i-1][j+1].rgbtBlue+imagea[i][j+1].rgbtBlue+imagea[i+1][j+1].rgbtBlue+imagea[i+1][j].rgbtBlue+imagea[i+1][j-1].rgbtBlue+imagea[i][j-1].rgbtBlue)/9.0f);

               image[i][j].rgbtRed =  tmpred;
           image[i][j].rgbtBlue =  tmpblue;
           image[i][j].rgbtGreen = tmpgreen;
            }
        }
    }
    return;
}
