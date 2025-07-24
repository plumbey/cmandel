// main.c
#include <stdio.h>

#include "argsparse.h"
#include "mandelbrot.h"

int main(int argc, char *argv[]) {
  MandelData mandelData;

  parse_args(argc, argv, &mandelData);

  printf("cMandel v0.2\n");
  printf("Width: %d\n", mandelData.width);
  printf("Height: %d\n", mandelData.height);
  printf("Delta: %lf\n", mandelData.delta);
  printf("X Center: %lf\n", mandelData.xCenter);
  printf("Y Center: %lf\n", mandelData.yCenter);
  printf("Max Iterations: %lf\n", mandelData.iterMax);
  printf("Hue Power: %lf\n", mandelData.huePower);
  printf("Darkness: %lf\n", mandelData.darkness);
  printf("Color-In: %s\n", mandelData.colorIn ? "true" : "false");
  printf("Output location: %s\n", mandelData.output);
  printf("Threads: %d\n\n", mandelData.numThreads);

  gdImagePtr img;
  img = gdImageCreateTrueColor(mandelData.width, mandelData.height);

  printf("Generating Mandelbrot\n");
  generateMandelbrot(img, &mandelData, mandelData.numThreads);

  FILE *pngout;
  pngout = fopen(mandelData.output, "wb");

  gdImagePng(img, pngout);

  printf("Done!\nCleaning up...\n");
  fclose(pngout);
  gdImageDestroy(img);
}
