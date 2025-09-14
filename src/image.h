#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <png.h>


typedef struct
{
    png_bytepp pixels;
    int width;
    int height;
} image;

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} pixel;

typedef struct {
    int h;
    float s;
    float v;
} hsv;

int initializeImage(image *img, int width, int height);
int writePng(FILE* fp, png_bytepp img, int width, int height);
void freeImage(image img);
png_bytepp createBlankImage(png_structp png_ptr, int width, int height);
hsv rgbToHsv(int rgbColor);
pixel hsvToRgb(hsv hsvColor);
int lerp(int x, int y, float fraction);
hsv lerpHsvHue(hsv color1, hsv color2, float fraction);
