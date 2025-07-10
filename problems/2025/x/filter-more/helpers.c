#include "helpers.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double avg = round(
                (double) (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE *temp_arr = malloc(width * sizeof(RGBTRIPLE));
    if (temp_arr == NULL)
    {
        return;
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp_arr[j] = image[i][j];
        }

        for (int j = 0; j < width; j++)
        {
            image[i][width - 1 - j] = temp_arr[j];
        }
    }

    free(temp_arr);
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Initialize a temp array
    RGBTRIPLE blur_arr[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // A counter to track the number of times it is adding up to divide by the average
            int count = 0;
            // Initialize the colors
            double rgbtBlue = 0;
            double rgbtGreen = 0;
            double rgbtRed = 0;

            // A loop to run 9 blocks around the pixels, avoiding the edges
            for (int row = i - 1; row <= i + 1; row++)
            {
                for (int col = j - 1; col <= j + 1; col++)
                {
                    if (row >= 0 && row < height && col >= 0 && col < width)
                    {
                        rgbtBlue += image[row][col].rgbtBlue;
                        rgbtGreen += image[row][col].rgbtGreen;
                        rgbtRed += image[row][col].rgbtRed;
                        count++;
                    }
                }
            }

            // Calculate the amount of blue by the average
            blur_arr[i][j].rgbtBlue = round(rgbtBlue / count);
            blur_arr[i][j].rgbtGreen = round(rgbtGreen / count);
            blur_arr[i][j].rgbtRed = round(rgbtRed / count);
        }
    }

    // Apply the blur on the origal image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = blur_arr[i][j];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Initialize a temp array
    RGBTRIPLE edges_arr[height][width];

    // Initialize the GX and GY kernels
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blue_gx = 0, blue_gy = 0;
            int green_gx = 0, green_gy = 0;
            int red_gx = 0, red_gy = 0;

            // A loop to run 9 blocks around the pixels, avoiding the edges
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    int row = i + k;
                    int col = j + l;

                    // Handle edges and corners
                    if (row < 0 || row >= height || col < 0 || col >= width)
                    {
                        continue;
                    }

                    // Caculate each pixel for both kernels
                    blue_gx += image[row][col].rgbtBlue * gx[k + 1][l + 1];
                    blue_gy += image[row][col].rgbtBlue * gy[k + 1][l + 1];
                    green_gx += image[row][col].rgbtGreen * gx[k + 1][l + 1];
                    green_gy += image[row][col].rgbtGreen * gy[k + 1][l + 1];
                    red_gx += image[row][col].rgbtRed * gx[k + 1][l + 1];
                    red_gy += image[row][col].rgbtRed * gy[k + 1][l + 1];
                }
            }

            int result_blue = round(sqrt(pow(blue_gx, 2) + pow(blue_gy, 2)));
            int result_green = round(sqrt(pow(green_gx, 2) + pow(green_gy, 2)));
            int result_red = round(sqrt(pow(red_gx, 2) + pow(red_gy, 2)));

            edges_arr[i][j].rgbtBlue = result_blue > 255 ? 255 : result_blue;
            edges_arr[i][j].rgbtGreen = result_green > 255 ? 255 : result_green;
            edges_arr[i][j].rgbtRed = result_red > 255 ? 255 : result_red;
        }
    }

    // Apply the edges on the origal image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = edges_arr[i][j];
        }
    }
}