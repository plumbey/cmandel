// palettes.c
#include "palettes.h"

const int lesbian[] = { 0xD52D00, 0xEF7627, 0xFF9A56, 0xFFFFFF,
			0xD162A4, 0xB55690, 0xA30262 };
const int trans[] = { 0x5BCEFA, 0xF5A9B8, 0xFFFFFF };
const int bisexual[] = { 0xD60270, 0x9B4F96, 0x0038A8 };
const int pansexual[] = { 0xFF218C, 0xFFD800, 0x21B1FF };
const int nonbinary[] = { 0xFFF430, 0xFFFFFF, 0x9C59D1, 0x000000 };
const int aromantic[] = { 0x3DA542, 0xA7D379, 0xFFFFFF, 0xA9A9A9, 0x000000 };
const int asexual[] = { 0x000000, 0xA4A4A4, 0xFFFFFF, 0x810081 };
const int rainbow[] = { 0xE40303, 0xFF8C00, 0xFFED00,
			0x008026, 0x004DFF, 0x750787 };

const Palette palette[] = { { "lesbian", lesbian, ARRAY_LEN(lesbian) },
			    { "trans", trans, ARRAY_LEN(trans) },
			    { "bisexual", bisexual, ARRAY_LEN(bisexual) },
			    { "pansexual", pansexual, ARRAY_LEN(pansexual) },
			    { "nonbinary", nonbinary, ARRAY_LEN(nonbinary) },
			    { "aromantic", aromantic, ARRAY_LEN(aromantic) },
			    { "asexual", asexual, ARRAY_LEN(asexual) },
			    { "rainbow", rainbow, ARRAY_LEN(rainbow) } };

const int numArrays = ARRAY_LEN(palette);

const Palette*
getArrayByName(const char* name)
{
	for (int i = 0; i < numArrays; i++) {
		if (strcasecmp(name, palette[i].name) == 0) {
			return &palette[i];
		}
	}
	return 0;
}
