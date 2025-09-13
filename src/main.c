// main.c
#include <stdio.h>

#include "mandelbrot.h"
#include "text_handle.h"
#include "image.h"

const char* log_path = "log.txt";

int main(int argc, char* argv[])
{
    MandelData mandel_data;

    int output_file_specified = parseArgs(argc, argv, &mandel_data);

    printf("cMandel v0.2\n");
    printMandelDataToStream(&mandel_data, stdout);

    printf("Generating Mandelbrot\n");

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) 
        return -1;
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) 
        return -1;

    png_set_IHDR(png_ptr, info_ptr, mandel_data.width, mandel_data.height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    png_bytepp img = createBlankImage(png_ptr, mandel_data.width, mandel_data.height);
    generateMandelbrot(img, &mandel_data);

    FILE* pngout;
    pngout = fopen(mandel_data.output, "wb");

    png_init_io(png_ptr, pngout);
    png_write_info(png_ptr, info_ptr);
    png_write_image(png_ptr, img);
    png_write_end(png_ptr, info_ptr);

    printf("Done!\nCleaning up...\n");

    png_destroy_write_struct(&png_ptr, &info_ptr);
    freeImage(png_ptr, img, mandel_data.height);

    if (appendMandelDataToFile(&mandel_data, log_path)) {
        printf("Added data to log file %s\n", log_path);
    }

    if (output_file_specified)
        free(mandel_data.output);

    fclose(pngout);
}
