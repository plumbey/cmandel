#include "mandelbrot.h"
#include <math.h>
#include "color.h"

double pointIterate(double x0, double y0, double max)
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

void generateMandelbrot(gdImagePtr img, MandelbrotData data)
{
    const double realLower = data.realCenter - data.coordinateDelta;
    const double realUpper = data.realCenter + data.coordinateDelta;

    const double imagLower = -data.imagCenter - data.coordinateDelta;
    const double imagUpper = -data.imagCenter + data.coordinateDelta;

    const double realDifference = realUpper - realLower;
    const double imagDifference = imagUpper - imagLower;

    for (int i = 0; i < data.pixelWidth; i++)
    {
        double real0 = realLower + realDifference * i / data.pixelWidth;
        for (int j = 0; j < data.pixelHeight; j++)
        {
            double imag0 = imagLower + realDifference * j / data.pixelHeight;
            double iterations = pointIterate(real0, imag0, data.maxIterations);
            hsv color;

            if (data.colorIn && iterations == data.maxIterations)
            {
                color.h = 0;
                color.s = 0;
                color.v = 0;
            } else {
                color.h = (int) (powf((iterations / data.maxIterations) * 360, data.hueIntensity)) % 360;
                color.s = 1;
                color.v = powf(iterations / data.maxIterations, data.darkness);
            };

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
