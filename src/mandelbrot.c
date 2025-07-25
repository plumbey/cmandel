// mandelbrot.c
#include "mandelbrot.h"

inline double pointIteratePeriodic(double x0, double y0, int max,
                                   double delta) {
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
        if ((x <= xold + margin && x >= xold - margin) &&
            (y <= yold + margin && y >= yold - margin)) {
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

void generateMandelbrot(gdImagePtr img, const MandelData *data,
                        int numThreads) {
    const double xLower = data->xCenter - data->delta;
    const double xUpper = data->xCenter + data->delta;

    const double yLower =
        -(data->yCenter) - data->delta * ((double)data->height / data->width);
    const double yUpper =
        -(data->yCenter) + data->delta * ((double)data->height / data->width);

    const double xDifference = xUpper - xLower;
    const double yDifference = yUpper - yLower;

    const double xStep = xDifference / data->width;
    const double yStep = yDifference / data->height;

    if (numThreads > 0) {
        omp_set_num_threads(numThreads);
    } else {
        omp_set_num_threads(omp_get_max_threads());
    }

#pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < data->width; i++) {
        //    printf("Thread %d is running number %d\n", omp_get_thread_num(),
        //    i);
        double x0 = xLower + i * xStep;

        for (int j = 0; j < data->height; j++) {
            double y0 = yLower + j * yStep;
            double iteration =
                pointIteratePeriodic(x0, y0, data->iterMax, data->delta);
            hsv color;

            if (data->colorIn && iteration == data->iterMax) {
                color.h = 0;
                color.s = 0;
                color.v = 0;
            } else {
                color.h = (int)(powf((iteration / data->iterMax) * 360,
                                     data->huePower)) %
                          360;
                color.s = 1;
                color.v = powf(iteration / data->iterMax, data->darkness);
            }

            int toAdd = allocHexToImage(img, hsvToRgb(color));
            gdImageSetPixel(img, i, j, toAdd);
        }
    }
}
