#include "color.h"
#include <math.h>

int allocHexToImage(gdImagePtr img, int color)
{
    return gdImageColorAllocate(img, (color >> 16) & 0xff, (color >> 8) & 0xff,
        color & 0xff);
}

// https://www.rapidtables.com/convert/color/rgb-to-hsv.html
hsv rgbToHsv(int rgbColor)
{
    float channels[3];
    channels[0] = (float)(((rgbColor >> 16) & 0xff)) / 255;
    channels[1] = (float)(((rgbColor >> 8) & 0xff)) / 255;
    channels[2] = (float)((rgbColor & 0xff)) / 255;
    float c_max = -1, c_min = 256;
    for (int i = 0; i < 3; i++) {
        c_max = channels[i] > c_max ? channels[i] : c_max;
        c_min = channels[i] < c_min ? channels[i] : c_min;
    }
    float delta = c_max - c_min;

    int h;
    if (delta == 0)
        h = 0;
    else if (c_max == channels[0])
        h = (int)(60 * fmod((channels[1] - channels[2]) / delta, 6));
    else if (c_max == channels[1])
        h = (int)(60 * (((channels[2] - channels[0]) / delta) + 2));
    else if (c_max == channels[2])
        h = (int)(60 * (((channels[0] - channels[1]) / delta) + 4));

    float s;
    s = c_max == 0 ? 0 : delta / c_max;

    float v = c_max;

    hsv ret = { h, s, v };
    return ret;
}

// https://www.rapidtables.com/convert/color/hsv-to-rgb.html
int hsvToRgb(hsv hsvColor)
{
    float c = hsvColor.v * hsvColor.s;
    float x = c * (1 - fabs(fmod(hsvColor.h / 60.0f, 2) - 1));
    float m = hsvColor.v - c;

    float channel_primes[3];

    if (hsvColor.h < 60) {
        channel_primes[0] = c;
        channel_primes[1] = x;
        channel_primes[2] = 0;
    } else if (hsvColor.h < 120) {
        channel_primes[0] = x;
        channel_primes[1] = c;
        channel_primes[2] = 0;
    } else if (hsvColor.h < 180) {
        channel_primes[0] = 0;
        channel_primes[1] = c;
        channel_primes[2] = x;
    } else if (hsvColor.h < 240) {
        channel_primes[0] = 0;
        channel_primes[1] = x;
        channel_primes[2] = c;
    } else if (hsvColor.h < 300) {
        channel_primes[0] = x;
        channel_primes[1] = 0;
        channel_primes[2] = c;
    } else {
        channel_primes[0] = c;
        channel_primes[1] = 0;
        channel_primes[2] = x;
    }

    int r = (int)((channel_primes[0] + m) * 255);
    int g = (int)((channel_primes[1] + m) * 255);
    int b = (int)((channel_primes[2] + m) * 255);

    return r << 16 | g << 8 | b;
}

int lerp(int x, int y, float fraction) { return (x - y) * fraction + x; }

hsv hsvLerpHue(hsv color1, hsv color2, float fraction)
{
    hsv ret = { lerp(color1.h, color2.h, fraction), color1.s, color1.v };
    return ret;
}
