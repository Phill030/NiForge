#pragma once
#include "Core/NiHeader.hpp"
#include "Reader.hpp"
#include "NiExtraData.hpp"

struct NIFORGE_API NiFloatExtraData : NiExtraData
{
	float floatData;
	NiFloatExtraData(Reader& reader, const NiHeader& header) : NiExtraData(reader, header) {
		floatData = reader.read<float>();
	}
};