#include "image.h"
#include <math.h>

png_bytepp createBlankImage(png_structp png_ptr, int width, int height)
{
    png_bytepp img = malloc(sizeof(png_bytep) * height);
    if (!img)
        return NULL;
    for (int i = 0; i < height; i++) {
        // each r, g, and b channel is one byte
        img[i] = malloc(sizeof(uint8_t) * width * 3);
        if (!img[i])
            return NULL;
    }
    return img;
}

void freeImage(png_structp png_ptr, png_bytepp img, int height)
{
    for (int i = 0; i < height; i++) {
        free(img[i]);
    }
    free(img);
}

int writePngToFile(png_structp png_ptr, png_infop info_ptr, FILE* fp, png_bytepp img, int width, int height)
{
    return 0;
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
pixel hsvToRgb(hsv hsvColor)
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

    pixel ret = {
        .r = (channel_primes[0] + m) * 255,
        .g = (channel_primes[1] + m) * 255,
        .b = (channel_primes[2] + m) * 255
    };

    return ret;
}

int lerp(int x, int y, float fraction) { return (x - y) * fraction + x; }

hsv hsvLerpHue(hsv color1, hsv color2, float fraction)
{
    hsv ret = { lerp(color1.h, color2.h, fraction), color1.s, color1.v };
    return ret;
}
