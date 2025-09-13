// mandelbrot.c

#include <math.h>

#include "image.h"
#include "mandelbrot.h"

inline double pointIteratePeriodic(double x0, double y0, int max,
    double delta)
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

void generateMandelbrot(png_bytepp img, const MandelData* data)
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

    for (int i = 0; i < data->height; i++) {
        double y0 = y_lower + i * y_step;
        int channel_in_row = 0;

        for (int j = 0; j < data->width; j++, channel_in_row += 3) {
            double x0 = x_lower + j * x_step;
            double iteration = pointIteratePeriodic(x0, y0, data->iterMax, data->delta);
            hsv color;

            if (data->colorIn && iteration == data->iterMax) {
                color.h = 0;
                color.s = 0;
                color.v = 0;
            } else {
                // https://en.wikipedia.org/wiki/Plotting_algorithms_for_the_Mandelbrot_set#HSV_coloring
                color.h = ((int)(powf((iteration / data->iterMax) * 360,
                               data->huePower))
                              + data->hueOffset)
                    % 360;
                color.s = 1;
                color.v = powf(iteration / data->iterMax, data->darkness);
            }
            pixel p = hsvToRgb(color);
            img[i][channel_in_row] = p.r;
            img[i][channel_in_row + 1] = p.g;
            img[i][channel_in_row + 2] = p.b;
        }
    }
}
