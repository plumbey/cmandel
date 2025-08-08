// main.c
#include <stdio.h>

#include "mandelbrot.h"
#include "text_handle.h"

const char* log_path = "log.txt";

int main(int argc, char* argv[])
{
    MandelData mandel_data;

    int output_file_specified = parseArgs(argc, argv, &mandel_data);

    printf("cMandel v0.2\n");
    printMandelDataToStream(&mandel_data, stdout);

    gdImagePtr img;
    img = gdImageCreateTrueColor(mandel_data.width, mandel_data.height);

    FILE* pngout;
    pngout = fopen(mandel_data.output, "wb");

    if (!pngout) {
        fprintf(stderr, "Error! Could not open file %s\n", mandel_data.output);
        if (output_file_specified)
            free(mandel_data.output);
        exit(1);
    }

    printf("Generating Mandelbrot\n");
    generateMandelbrot(img, &mandel_data);

    gdImagePng(img, pngout);

    printf("Done!\nCleaning up...\n");

    if (appendMandelDataToFile(&mandel_data, log_path)) {
        printf("Added data to log file %s\n", log_path);
    }

    if (output_file_specified)
        free(mandel_data.output);

    gdImageDestroy(img);
    fclose(pngout);
}
