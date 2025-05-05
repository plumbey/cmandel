#include "mandelbrot.h"

int main(void)
{
    gdImagePtr image;
    image = gdImageCreate(WIDTH, HEIGHT);
    int palette[5];
    int light = gdImageColorAllocate(image, 251,241,199);
    int yellow = gdImageColorAllocate(image, 215,153,33);
    int orange = gdImageColorAllocate(image, 214,93,14);
    int red = gdImageColorAllocate(image, 204, 36, 29);
    int dark = gdImageColorAllocate(image, 29,32,33);
    palette[0] = light;
    palette[1] = yellow;
    palette[2] = orange;
    palette[3] = red;
    palette[4] = dark;

    FILE* pngout;
    pngout = fopen("output.png", "wb");

    mandelbrot(image, palette, 5);
    gdImagePng(image, pngout);
    
    fclose(pngout);
    gdImageDestroy(image);
}

