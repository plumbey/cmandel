#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <gd.h>
#include <math.h>
#include "color.h"

static const int WIDTH = 1000;
static const int HEIGHT = 1000;

static const double xCenter = -0.74450100005;
static const double yCenter = -0.15141000025;
static const double delta = 0.00000000001;

// Feel free to mess with these for proper coloring
// maximum Iterations, as these increase, the background tends to become darker
static const double max = 2000;
// the power by which the hue is raised to, as this increases, the image becomes more rainbow
static const double hueIntensity = 0.9;
// the power by which the value is raised to, as this increases, the image becomes darker
static const double darkness = 0.2;


double pointIterate(double x0, double y0, int max);
void generateMandelbrot(gdImagePtr img);
#endif
