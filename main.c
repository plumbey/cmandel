#include "mandelbrot.h"

int main(void)
{
    gdImagePtr img;
    img = gdImageCreateTrueColor(WIDTH, HEIGHT);

    generateMandelbrot(img, 1);
    
    FILE* pngout;
    pngout = fopen("output.png", "wb");

    gdImagePng(img, pngout);
    
    fclose(pngout);
    gdImageDestroy(img);
}

