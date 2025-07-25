// argsparse.h
#ifndef ARGSPARSE_H
#define ARGSPARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mandelbrot.h"

int parse_args(int argc, char *argv[], MandelData *data);
// returns 0 if output file is specified, 1 if it is
// use this to free the MandelData's .output field.

#endif // !ARGSPARSE_H
