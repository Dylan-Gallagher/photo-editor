#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // I have to average each of the RGB values and set them all to be the same
    // Loop through each row
    for (int i = 0; i < height; i++)
    {
        // Loop through each pixel in the row
        for (int j = 0; j < width; j++)
        {
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;
            float float_avg = (red + green + blue) / 3;
            int int_avg = round(float_avg);
            image[i][j].rgbtRed = int_avg;
            image[i][j].rgbtGreen = int_avg;
            image[i][j].rgbtBlue = int_avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through each row
    for (int i = 0; i < height; i++)
    {
        // Loop through each pixel in the row
        for (int j = 0; j < width; j++)
        {
            // Import each pixel channel
            float originalRed = image[i][j].rgbtRed;
            float originalGreen = image[i][j].rgbtGreen;
            float originalBlue = image[i][j].rgbtBlue;

            // Apply Sepia formula
            float sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            float sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            float sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;

            // Round to nearest integer
            sepiaRed = round(sepiaRed);
            sepiaGreen = round(sepiaGreen);
            sepiaBlue = round(sepiaBlue);

            // Cap them to 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Replace pixels with sepia pixels
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through each row
    for (int i = 0; i < height; i++)
    {
        // Reverse the array
        int start = 0;
        int end = width - 1;

        while (start < end)
        {
            RGBTRIPLE temp = image[i][start];
            image[i][start] = image[i][end];
            image[i][end] = temp;
            start++;
            end--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy of the image 2d array
    RGBTRIPLE imageCopy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imageCopy[i][j] = image[i][j];
        }
    }

    // Blur each pixel (not counting edge pixels)
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            // Populate pixels array
            RGBTRIPLE pixels[3][3];
            for (int l = -1; l <= 1; l++)
            {
                for (int m = -1; m <= 1; m++)
                {
                    pixels[l + 1][m + 1] = imageCopy[i + l][j + m];
                }
            }

            // Apply blur algorithm
            // I have a 2d array that (for each pixel) has the RGBTRIPLE data of each surrounding pixel
            // I can average the R G and B values for each pixel in the array and change the middle pixel to the average of each

            float avgRed = 0.0;
            float avgGreen = 0.0;
            float avgBlue = 0.0;

            // For every row of the pixels 2d array
            for (int a = 0; a < 3; a++)
            {
                // For every pixel of the row
                for (int b = 0; b < 3; b++)
                {
                    float red = pixels[a][b].rgbtRed;
                    float green = pixels[a][b].rgbtGreen;
                    float blue = pixels[a][b].rgbtBlue;

                    avgRed += red;
                    avgGreen += green;
                    avgBlue += blue;
                }
            }
            // Get the average red, green and blue
            avgRed /= 9;
            avgGreen /= 9;
            avgBlue /= 9;

            // Round the averages
            avgRed = round(avgRed);
            avgGreen = round(avgGreen);
            avgBlue = round(avgBlue);

            // Make the centre pixel the average
            image[i][j].rgbtRed = avgRed;
            image[i][j].rgbtGreen = avgGreen;
            image[i][j].rgbtBlue = avgBlue;
        }
    }
    return;
}
