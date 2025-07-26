// palette.h
#pragma once
#include <strings.h>
#define ARRAY_LEN(a) ((unsigned int)(sizeof(a) / sizeof((a)[0])))

typedef struct {
	const char* name;
	const int* data;
	unsigned int size;
} Palette;

extern const int lesbian[];
extern const int trans[];

extern const Palette palette[];
extern const int numArrays;

const Palette* getArrayByName(const char* name);
