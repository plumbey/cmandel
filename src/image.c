#include "image.h"
#include <math.h>

int initializeImage(image *img, int width, int height)
{
    img->width = width;
    img->height = height;

    img->pixels = malloc(sizeof(png_bytep) * height);
    if (!img->pixels)
        return -1;
    for (int i = 0; i < height; i++) {
        // each r, g, and b channel is one byte
        img->pixels[i] = malloc(sizeof(uint8_t) * width * 3);
        if (!img->pixels[i])
            return -1;
    }

    img->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!img->png_ptr) 
        return -1;
    img->info_ptr = png_create_info_struct(img->png_ptr);
    if (!img->info_ptr) 
        return -1;

    return 0;
}

void freeImage(image *img)
{
    for (int i = 0; i < img->height; i++) {
        free(img->pixels[i]);
    }
    free(img->pixels);
    png_destroy_write_struct(&img->png_ptr, &img->info_ptr);
}

void writeImageToFile(image *img, FILE* fp)
{
    png_set_IHDR(img->png_ptr, img->info_ptr, img->width, img->height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_init_io(img->png_ptr, fp);
    png_write_info(img->png_ptr, img->info_ptr);
    png_write_image(img->png_ptr, img->pixels);
    png_write_end(img->png_ptr, img->info_ptr);
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
