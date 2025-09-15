// main.c
#include <stdio.h>

#include "mandelbrot.h"
#include "text_handle.h"
#include "image.h"

const char* log_path = "log.txt";

int main(int argc, char* argv[])
{
    MandelData mandel_data = createDefaultMandelData();

    int output_file_specified = parseArgs(argc, argv, &mandel_data);

    printf("cMandel v0.3\n");
    printMandelDataToStream(&mandel_data, stdout);

    FILE* output_file;
    output_file = fopen(mandel_data.output, "wb");

    if (!output_file) {
        fprintf(stderr, "Error! Could not open file %s\n", mandel_data.output);
        if (output_file_specified)
            free(mandel_data.output);
        exit(1);
    }

    printf("Creating image\n");

    image img;
    if (initializeImage(&img, mandel_data.width, mandel_data.height) == -1)
    {
        printf("Error! Unable to initialize image. Exiting...\n");
        if (output_file_specified)
            free(mandel_data.output);
        exit(-1);
    }

    printf("Generating Mandelbrot Set\n");

    generateMandelbrotImage(&img, &mandel_data);

    writeImageToFile(&img, output_file);

    if (appendMandelDataToFile(&mandel_data, log_path)) {
        printf("Added data to log file %s\n", log_path);
    }

    printf("Done!\nCleaning up...\n");

    freeImage(&img);
    if (output_file_specified)
        free(mandel_data.output);

    fclose(output_file);
}
