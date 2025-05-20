#include "mandelbrot.h"

double pointIterate(double x0, double y0, int max)
{
    double x = 0, y = 0;
    double iterations = 0;

    while ((x*x + y*y) <= (1 << 16) && iterations < max)
    {
        double xtemp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtemp;
        iterations++;
    }

    return iterations;
}

void generateMandelbrot(gdImagePtr img)
{
    double xDifference = xUpper - xLower;
    double yDifference = yUpper - yLower;

    for (int i = 0; i < WIDTH; i++)
    {
        double x0 = xLower + xDifference * i / WIDTH;
        for (int j = 0; j < HEIGHT; j++)
        {
            double y0 = yLower + xDifference * j / HEIGHT;
            double iteration = pointIterate(x0, y0, max);
            hsv color = {(int) (powf((iteration / max) * 360, hueIntensity)) % 360, 1, iteration / max};
            int toAdd = allocHexToImage(img, hsvToRgb(color));
            gdImageSetPixel(img, i, j, toAdd);
        }
    }
}

/*
double pointIterateLerp(double x0, double y0, int max)
{
    double log_2 = 0.6931471805599;
    double x = 0, y = 0;
    int iterations;

    while ((x*x + y*y) <= (1 << 16) && iterations < max)
    {
        double xtemp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtemp;
        iterations++;
    }

    if (iterations < max)
    {
        double log_zn = log(x*x + y*y) / 2;
        double nu = log(log_zn / log_2) / log_2;
        iterations = iterations + 1 - nu;
    }

    return iterations;
}
*/
