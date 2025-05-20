#include "mandelbrot.h"

int main(void)
{
    gdImagePtr img;
    img = gdImageCreateTrueColor(WIDTH, HEIGHT);

    generateMandelbrot(img);
    
    FILE* pngout;
    pngout = fopen("output.png", "wb");

    gdImagePng(img, pngout);
    
    fclose(pngout);
    gdImageDestroy(img);
}

