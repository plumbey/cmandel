#include "mandelbrot.h"

int chooseColorFromIterations(int* palette, size_t length, int num, int numBound)
{
    if (num < (float) numBound / length)
        return palette[0];
    else if (num > numBound - numBound / length)
        return palette[length - 1];
    else
        return palette[length * num / numBound - 1];
}

void mandelbrot(gdImagePtr image, int *palette, size_t palette_len)
{

    for (int i = 0; i < HEIGHT; i++)
    {
        double complex c_i = z_lower + (cimag(difference) * i / HEIGHT) * I;
        for (int j = 0; j < WIDTH; j++)
        {
            double complex c_ij = c_i + (creal(difference) * j / WIDTH);
            double complex z = 0.0 + 0.0 * I;

            int iterations = 0;
            while (cabs(z) <= 2 && iterations < ITERATION_LIMIT)
            {
                /*
                 RECURSIVE EQUATION
                */
                z = z * z + c_ij;
                iterations++;
            }
            gdImageSetPixel(image, j, i, 
                            chooseColorFromIterations(palette, palette_len, iterations, ITERATION_LIMIT));
        }
    }
}
