// mandelbrot.c
#include <math.h>

#include "color.h"
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

void generateMandelbrot(gdImagePtr img, const MandelData* data)
{
    const double x_lower = data->xCenter - data->delta;
    const double x_upper = data->xCenter + data->delta;

    const double y_lower = -(data->yCenter) - data->delta * ((double)data->height / data->width);
    const double y_upper = -(data->yCenter) + data->delta * ((double)data->height / data->width);

    const double x_difference = x_upper - x_lower;
    const double y_difference = y_upper - y_lower;

    const double x_step = x_difference / data->width;
    const double y_step = y_difference / data->height;

    for (int i = 0; i < data->width; i++) {
        double x0 = x_lower + i * x_step;

        for (int j = 0; j < data->height; j++) {
            double y0 = y_lower + j * y_step;
            double iteration = pointIteratePeriodic(x0, y0, data->iterMax, data->delta);
            hsv color;

            if (data->colorIn && iteration == data->iterMax) {
                color.h = 0;
                color.s = 0;
                color.v = 0;
            } else {
                color.h = ((int)(powf((iteration / data->iterMax) * 360,
                               data->huePower))
                              + data->hueOffset)
                    % 360;
                color.s = 1;
                color.v = powf(iteration / data->iterMax, data->darkness);
            }

            int to_add = allocHexToImage(img, hsvToRgb(color));
            gdImageSetPixel(img, i, j, to_add);
        }
    }
}
