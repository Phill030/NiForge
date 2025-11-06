#pragma once
#include "Reader.hpp"
#include "Core/NiHeader.hpp"
#include "NiTexture.hpp"
#include <cstdint>
#include <string>

struct NIFORGE_API NiSourceTexture : NiTexture
{
public:
	uint8_t useExternal;
	std::string filePath;
	int32_t unknownLink; // Ref<NiObject>  possibly PixelData?
	FormatPrefs formatPrefs;
	uint8_t isStatic;
	bool directRender;
	bool persistRenderData;

	NiSourceTexture(Reader& reader, const NiHeader& header): NiTexture(reader, header) {
		useExternal = reader.read<uint8_t>();
		filePath = header.getIndexString(reader);
		unknownLink = reader.read<int32_t>();
		formatPrefs = FormatPrefs(reader, header);
		isStatic = reader.read<uint8_t>();
		directRender = reader.read<bool>();
		persistRenderData = reader.read<bool>();
	}
};