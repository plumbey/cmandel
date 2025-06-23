#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <gd.h>
#include <math.h>
#include "color.h"

typedef struct 
{
    uint64_t pixelWidth; 
    uint64_t pixelHeight;
    double coordinateDelta;
    double realCenter; 
    double imagCenter; 
    double maxIterations;
    double hueIntensity;
    double darkness; 
} MandelbrotData;


double pointIterate(double x0, double y0, double max);
void generateMandelbrot(gdImagePtr img, MandelbrotData data);
#endif
