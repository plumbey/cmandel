#ifndef COLOR_H
#define COLOR_H

#include <math.h>
#include <gd.h>
#include <stdint.h>

typedef struct 
{
    uint32_t h;
    float s;
    float v;
}
hsv;

uint32_t allocHexToImage(gdImagePtr img, uint32_t color);
hsv rgbToHsv(uint32_t rgbColor);
uint32_t hsvToRgb(hsv hsvColor);
uint32_t lerp(uint32_t x, uint32_t y, float fraction);
hsv lerpHsvHue(hsv color1, hsv color2, float fraction);

#endif
