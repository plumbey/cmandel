#ifndef MANDELBROT_H
#define MANDELBROT_H
#include <stdio.h>
#include <gd.h>
#include <complex.h>

#define WIDTH 2560
#define HEIGHT 1440
#define ITERATION_LIMIT 12

int chooseColorFromIterations(int* palette, size_t length, int num, int numBound);
void mandelbrot(gdImagePtr image, int *palette, size_t palette_len);

static const double complex z_lower = -2.00 - 1.2 * I;
static const double complex z_upper = 0.6 + 1.2 * I;
static const double complex difference = z_upper - z_lower;
#endif
