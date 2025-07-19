// main.c
#include <stdio.h>

#include "argsparse.h"
#include "mandelbrot.h"

int WIDTH = 3000;
int HEIGHT = 3000;

int main(int argc, char *argv[]) {
  parse_args(argc, argv, &WIDTH, &HEIGHT);

  printf("cMandel v0.2\n");
  printf("Width: %i\nHeight: %i\n", WIDTH, HEIGHT);
  gdImagePtr img;
  img = gdImageCreateTrueColor(WIDTH, HEIGHT);

  printf("Generating Mandelbrot\n");
  generateMandelbrot(img, 1);

  FILE *pngout;
  pngout = fopen("output.png", "wb");

  gdImagePng(img, pngout);

  printf("Done!\nCleaning up...\n");
  fclose(pngout);
  gdImageDestroy(img);
}
