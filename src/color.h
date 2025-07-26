#pragma once

#include <gd.h>
#include "palettes.h"

typedef struct {
	int h;
	float s;
	float v;
} hsv;

int allocHexToImage(gdImagePtr img, int color);
hsv rgbToHsv(int rgbColor);
int hsvToRgb(hsv hsvColor);
int hsvToPal(hsv hsvColor, const Palette *palette);
int lerp(int x, int y, float fraction);
hsv lerpHsvHue(hsv color1, hsv color2, float fraction);
