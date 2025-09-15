// mandelbrot.c
#include <math.h>
#include <omp.h>
#include "image.h"
#include "mandelbrot.h"

void generateMandelbrotImage(image *img, const MandelData* data)
{
    const double x_lower = data->xCenter - data->delta;
    const double x_upper = data->xCenter + data->delta;

    // crop the y values if the image height is not square
    const double y_lower = -(data->yCenter) - data->delta * ((double)data->height / data->width);
    const double y_upper = -(data->yCenter) + data->delta * ((double)data->height / data->width);

    const double x_difference = x_upper - x_lower;
    const double y_difference = y_upper - y_lower;

    const double x_step = x_difference / data->width;
    const double y_step = y_difference / data->height;

#pragma omp parallel for
    for (int i = 0; i < data->height; i++) {
        double y0 = y_lower + i * y_step;

        for (int j = 0; j < data->width; j++) {
            double x0 = x_lower + j * x_step;
            double iterations = pointIteratePeriodic(x0, y0, data->iterMax, data->delta);

            hsv hsv_color = {0};

            if (iterations < data->iterMax || !data->colorIn) {
                hsv_color = iterationsToHSV(iterations, data);
            }

            pixel p = hsvToRgb(hsv_color);

            addPixelToImage(p, img, j, i);
        }
    }
}

void addPixelToImage(pixel p, image *img, int xval, int yval)
{
    const int channels_per_pixel = 3;
    const int x_index = channels_per_pixel * xval;

    img->pixels[yval][x_index] = p.r;
    img->pixels[yval][x_index + 1] = p.g;
    img->pixels[yval][x_index + 2] = p.b;
}

hsv iterationsToHSV(const double iterations, const MandelData *data)
{
    hsv color;

    // https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set#HSV_coloring
    color.h = ((int)(powf((iterations / data->iterMax) * 360,
                   data->huePower))
                  + data->hueOffset)
        % 360;
    color.s = 1;
    color.v = powf(iterations / data->iterMax, data->darkness);

    return color;
}

double pointIteratePeriodic(double x0, double y0, int max, double delta)
{
    double x = 0, y = 0;
    double xold = 0, yold = 0;
    double iterations = 0, period = 0;

    // margin of error for periodicity checking
    const int period_len = 32;
    const double margin = delta / (period_len * 1000);

    while ((x * x + y * y) <= (1 << 16) && iterations < max) {
        double xtemp = x * x - y * y + x0;
        y = 2 * x * y + y0;
        x = xtemp;
        iterations++;

        // break if we're repeating
        if ((x <= xold + margin && x >= xold - margin) && (y <= yold + margin && y >= yold - margin)) {
            iterations = max;
            break;
        }

        period++;
        if (period > period_len) {
            period = 0;
            xold = x;
            yold = y;
        }
    }

    return iterations;
}

MandelData createDefaultMandelData()
{
    MandelData data;

    data.width = 2000;
    data.height = 2000;
    data.delta = 1.0;
    data.xCenter = -0.5;
    data.yCenter = 0;
    data.iterMax = 1024;
    data.huePower = 1.2;
    data.darkness = 0;
    data.colorIn = true;
    data.hueOffset = 0;
    data.output = "./output.png";

    return data;
}

