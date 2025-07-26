// mandelbrot.h
#pragma once

#include <gd.h>
#include <stdbool.h>
#include "palettes.h"

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
	char *output;
	// color palette to use
	char *palette;
	// the actual colors
	const Palette *colors;
} MandelData;

double pointIteratePeriodic(double x0, double y0, int max, double delta);
void generateMandelbrot(gdImagePtr img, const MandelData *data);
