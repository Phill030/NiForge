#pragma once
#include "Core/NiHeader.hpp"
#include "Reader.hpp"
#include "NiExtraData.hpp"
#include <cstdint>

struct NiIntegerExtraData : NiExtraData
{
	uint32_t integerData;
	NiIntegerExtraData(Reader& reader, const NiHeader& header) : NiExtraData(reader, header) {
		integerData = reader.read<uint32_t>();
	}
};