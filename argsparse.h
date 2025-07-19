// argsparse.h
#ifndef ARGSPARSE_H
#define ARGSPARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void parse_args(int argc, char *argv[], int *w, int *h) {
  *w = 3000;
  *h = 3000;

  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], "-w") == 0 && i + 1 < argc) {
      *w = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-h") == 0 && i + 1 < argc) {
      *h = atoi(argv[++i]);
    }
  }
}

#endif  // !ARGSPARSE_H
