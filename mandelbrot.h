#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <gd.h>
#include <math.h>
#include "color.h"

static const int WIDTH = 1000;
static const int HEIGHT = 1000;

static const double xCenter = -0.744501;
static const double yCenter = -0.15141;
static const double delta = 0.00001;

static const double xLower = xCenter - delta;
static const double xUpper = xCenter + delta;

static const double yLower = yCenter - delta;
static const double yUpper = yCenter + delta;

static const double hueIntensity = 0.6;
static const double max = 1000;

double pointIterate(double x0, double y0, int max);
void generateMandelbrot(gdImagePtr img);
#endif
