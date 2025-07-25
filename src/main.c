// main.c
#include <stdio.h>

#include "text_handle.h"
#include "mandelbrot.h"

const char *LOG_PATH = "log.txt";

int main(int argc, char *argv[]) {
    MandelData mandelData;

    int outputFileSpecified = parseArgs(argc, argv, &mandelData);

    printf("cMandel v0.2\n");
    printMandelDataToStream(&mandelData, stdout);

    gdImagePtr img;
    img = gdImageCreateTrueColor(mandelData.width, mandelData.height);

    printf("Generating Mandelbrot\n");
    generateMandelbrot(img, &mandelData);

    FILE *pngout;
    pngout = fopen(mandelData.output, "wb");

    if (outputFileSpecified) 
        free(mandelData.output);

    gdImagePng(img, pngout);

    printf("Done!\nCleaning up...\n");
    fclose(pngout);

    if (appendMandelDataToFile(&mandelData, LOG_PATH)) {
        printf("Added data to log file %s\n", LOG_PATH);
    }
    gdImageDestroy(img);
}
