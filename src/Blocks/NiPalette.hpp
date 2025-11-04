#pragma once
#include "../../Types/Color4.hpp"
#include "../Reader.hpp"
#include "NiObject.hpp"
#include <cstdint>

//NiPalette objects represent mappings from 8-bit indices to 24-bit RGB or 32-bit RGBA colors. 
struct NiPalette : NiObject
{
	uint8_t hasAlpha;
	uint32_t numEntries;
	Color4 Palette;
	NiPalette(Reader& reader) {
		hasAlpha = reader.read<uint8_t>();
		numEntries = reader.read<uint32_t>();
		Palette = reader.read<Color4>();
	}
};