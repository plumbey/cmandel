#include <math.h>
#include <gd.h>
#include "color.h"

uint32_t allocHexToImage(gdImagePtr img, uint32_t color)
{
   return gdImageColorAllocate(img,
                        (color >> 16) & 0xff,
                        (color >> 8) & 0xff,
                        color & 0xff);
}

// https://www.rapidtables.com/convert/color/rgb-to-hsv.html
hsv rgbToHsv(uint32_t rgbColor)
{
    float channels[3];
    channels[0] = (float)(((rgbColor >> 16) & 0xff)) / 255;
    channels[1] = (float)(((rgbColor >> 8) & 0xff)) / 255;
    channels[2] = (float)((rgbColor & 0xff)) / 255;
    float cMax = -1, cMin = 256;
    for (uint32_t i = 0; i < 3; i++)
    {
        cMax = channels[i] > cMax ? channels[i] : cMax;
        cMin = channels[i] < cMin ? channels[i] : cMin;
    }
    float delta = cMax - cMin;

    uint32_t H;
    if (delta == 0)
        H = 0;
    else if (cMax == channels[0])
        H = (uint32_t) (60 * fmod((channels[1] - channels[2]) / delta, 6));
    else if (cMax == channels[1])
        H = (uint32_t) (60 * (((channels[2] - channels[0]) / delta) + 2));
    else if (cMax == channels[2])
        H = (uint32_t) (60 * (((channels[0] - channels[1]) / delta) + 4));

    float S;
    S = cMax == 0 ? 0 : delta / cMax;

    float V = cMax;

    hsv ret = {H, S, V};
    return ret;
}

// https://www.rapidtables.com/convert/color/hsv-to-rgb.html
uint32_t hsvToRgb(hsv hsvColor)
{
    float C = hsvColor.v * hsvColor.s; 
    float X = C * (1 - fabs(fmod(hsvColor.h / 60.0f, 2) - 1));
    float m = hsvColor.v - C;

    float channelPrimes[3];

    if (hsvColor.h < 60)
    {
        channelPrimes[0] = C;
        channelPrimes[1] = X;
        channelPrimes[2] = 0;
    }
    else if (hsvColor.h < 120)
    {
        channelPrimes[0] = X;
        channelPrimes[1] = C;
        channelPrimes[2] = 0;
    }
    else if (hsvColor.h < 180)
    {
        channelPrimes[0] = 0;
        channelPrimes[1] = C;
        channelPrimes[2] = X;
    }
    else if (hsvColor.h < 240)
    {
        channelPrimes[0] = 0;
        channelPrimes[1] = X;
        channelPrimes[2] = C;
    }
    else if (hsvColor.h < 300)
    {
        channelPrimes[0] = X;
        channelPrimes[1] = 0;
        channelPrimes[2] = C;
    }
    else
    {
        channelPrimes[0] = C;
        channelPrimes[1] = 0;
        channelPrimes[2] = X;
    }

    uint32_t r = (uint32_t) ((channelPrimes[0] + m) * 255);
    uint32_t g = (uint32_t) ((channelPrimes[1] + m) * 255);
    uint32_t b = (uint32_t) ((channelPrimes[2] + m) * 255);

    return r << 16 | g << 8 | b;
}

uint32_t lerp(uint32_t x, uint32_t y, float fraction)
{
    return (x - y) * fraction + x;
}

hsv hsvLerpHue(hsv color1, hsv color2, float fraction)
{
    hsv ret = {lerp(color1.h, color2.h, fraction), color1.s, color1.v};
    return ret;
}
