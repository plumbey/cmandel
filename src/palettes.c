#include "palettes.h"

const int lesbian[] = { 0xD52D00, 0xEF7627, 0xFF9A56, 0xFFFFFF,
			0xD162A4, 0xB55690, 0xA30262 };
const int trans[] = { 0x5BCEFA, 0xF5A9B8, 0xFFFFFF };

const Palette palette[] = { { "lesbian", lesbian, ARRAY_LEN(lesbian) },
			    { "trans", trans, ARRAY_LEN(trans) } };

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
