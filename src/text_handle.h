// argsparse.h
#pragma once

#include "mandelbrot.h"

void printHelp();
int printMandelDataToStream(const MandelData* data, FILE* stream);
int appendMandelDataToFile(const MandelData* data, const char* path);
int parseArgs(int argc, char* argv[], MandelData* data);
// returns 0 if output file is specified, 1 if it is
// use this to free the MandelData's .output field.
