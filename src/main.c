// main.c
#include <stdio.h>

#include "argsparse.h"
#include "mandelbrot.h"

MandelData mandelData = {
    .width = 3000,
    .height = 3000,
    .delta = 1.0,
    .xCenter = -0.5,
    .yCenter = 0,
    .iterMax = 1024,
    .huePower = 1.2,
    .darkness = 0.00,
    .colorIn = true,
};

int main(int argc, char *argv[]) {
  parse_args(argc, argv, &mandelData.width, &mandelData.height);

  printf("cMandel v0.2\n");
  printf("Width: %i\nHeight: %i\n", mandelData.width, mandelData.height);
  gdImagePtr img;
  img = gdImageCreateTrueColor(mandelData.width, mandelData.height);

  printf("Generating Mandelbrot\n");
  generateMandelbrot(img, &mandelData);

  FILE *pngout;
  pngout = fopen("output.png", "wb");

  gdImagePng(img, pngout);

  printf("Done!\nCleaning up...\n");
  fclose(pngout);
  gdImageDestroy(img);
}
