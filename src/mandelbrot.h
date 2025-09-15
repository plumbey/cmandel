// mandelbrot.h
#pragma once
#include <stdbool.h>
#include "image.h"

typedef struct {
    int width;
    int height;
    double delta;
    double xCenter;
    double yCenter;
    // maximum Iterations, as these increase, the background tends to become darker
    double iterMax;
    /* the power by which the hue is raised to, as this increases, the image
       becomes more rainbow */
    double huePower;
    /* the power by which the value is raised to, as this increases, the
       background becomes darker */
    double darkness;
    // color in the set black
    bool colorIn;
    // offset to change the background color (from 0 - 360)
    int hueOffset;
    // output file path
    char* output;
} MandelData;

void generateMandelbrotImage(image* img, const MandelData* data);
double pointIteratePeriodic(const double x0, const double y0, const int max, const double delta);
hsv iterationsToHSV(const double iterations, const MandelData *data);
void addPixelToImage(pixel p, image *img, int xval, int yval);
MandelData createDefaultMandelData();
