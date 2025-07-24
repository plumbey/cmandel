// mandelbrot.h
#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <gd.h>
#include <math.h>
#include <omp.h>
#include <stdbool.h>

#include "color.h"

typedef struct {
  int width;
  int height;
  double delta;
  double xCenter;
  double yCenter;
  // maximum Iterations, as these increase, the background tends to become
  // darker
  double iterMax;
  /* the power by which the hue is raised to, as this increases, the image
     becomes more rainbow */
  double huePower;
  /* the power by which the value is raised to, as this increases, the
     background becomes darker */
  double darkness;
  // color in the set black
  bool colorIn;
  // output file path
  const char *output;
  // number of threads to use
  int numThreads;
} MandelData;

double pointIteratePeriodic(double x0, double y0, int max, double delta);
void generateMandelbrot(gdImagePtr img, const MandelData *data, int numThreads);
#endif
