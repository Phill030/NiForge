#pragma once
#include "Core/NiHeader.hpp"
#include "Reader.hpp"
#include "NiExtraData.hpp"
#include <cstdint>

struct NiBooleanExtraData : NiExtraData
{
	uint8_t booleanData; // The boolean extra data value.
	NiBooleanExtraData(Reader& reader, const NiHeader& header) : NiExtraData(reader, header) {
		booleanData = reader.read<uint8_t>();
	}
};