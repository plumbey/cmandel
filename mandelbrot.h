// mandelbrot.h
#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <gd.h>
#include <math.h>

#include "argsparse.h"
#include "color.h"

extern int WIDTH;
extern int HEIGHT;

static const double delta = 1.0;
static const double xCenter = -0.5;
static const double yCenter = 0;

// Feel free to mess with these for proper coloring

// maximum Iterations, as these increase, the background tends to become darker
static const double max = 1000;
// the power by which the hue is raised to, as this increases, the image becomes
// more rainbow
static const double hueIntensity = 1.2;
// the power by which the value is raised to, as this increases, the background
// becomes darker
static const double darkness = .025;

double pointIterate(double x0, double y0, int max);
void generateMandelbrot(gdImagePtr img, int colorIn);
#endif
