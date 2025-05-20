#ifndef COLOR_H
#define COLOR_H

#include <math.h>
#include <gd.h>

typedef struct 
{
    int h;
    float s;
    float v;
}
hsv;

int allocHexToImage(gdImagePtr img, int color);
hsv rgbToHsv(int rgbColor);
int hsvToRgb(hsv hsvColor);
int lerp(int x, int y, float fraction);
hsv lerpHsvHue(hsv color1, hsv color2, float fraction);

#endif
