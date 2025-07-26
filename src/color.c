#include "color.h"
#include "mandelbrot.h"
#include <math.h>

int
allocHexToImage(gdImagePtr img, int color)
{
	return gdImageColorAllocate(img, (color >> 16) & 0xff,
				    (color >> 8) & 0xff, color & 0xff);
}

// https://www.rapidtables.com/convert/color/rgb-to-hsv.html
hsv
rgbToHsv(int rgbColor)
{
	float channels[3];
	channels[0] = (float)(((rgbColor >> 16) & 0xff)) / 255;
	channels[1] = (float)(((rgbColor >> 8) & 0xff)) / 255;
	channels[2] = (float)((rgbColor & 0xff)) / 255;
	float cMax = -1, cMin = 256;
	for (int i = 0; i < 3; i++) {
		cMax = channels[i] > cMax ? channels[i] : cMax;
		cMin = channels[i] < cMin ? channels[i] : cMin;
	}
	float delta = cMax - cMin;

	int H;
	if (delta == 0)
		H = 0;
	else if (cMax == channels[0])
		H = (int)(60 * fmod((channels[1] - channels[2]) / delta, 6));
	else if (cMax == channels[1])
		H = (int)(60 * (((channels[2] - channels[0]) / delta) + 2));
	else if (cMax == channels[2])
		H = (int)(60 * (((channels[0] - channels[1]) / delta) + 4));

	float S;
	S = cMax == 0 ? 0 : delta / cMax;

	float V = cMax;

	hsv ret = { H, S, V };
	return ret;
}

// https://www.rapidtables.com/convert/color/hsv-to-rgb.html
int
hsvToPal(hsv hsvColor, Palette *palette)
{
	int hue = hsvColor.h % 360;
	if (hue < 0)
		hue += 360;
	float slice_size = 360.0f / palette->size;
	int index = (int)(hue / slice_size);
	if (index >= palette->size)
		index = palette->size - 1; // Just in case

	return palette->data[index];
}

int
lerp(int x, int y, float fraction)
{
	return (x - y) * fraction + x;
}

hsv
hsvLerpHue(hsv color1, hsv color2, float fraction)
{
	hsv ret = { lerp(color1.h, color2.h, fraction), color1.s, color1.v };
	return ret;
}
