#pragma once
#include "../../Core/NiHeader.hpp"
#include "../../Reader.hpp"
#include "NiProperty.hpp"
#include <cstdint>

struct NiAlphaProperty : NiProperty
{
public:
	uint16_t flags;
	uint8_t threshold;
	NiAlphaProperty(Reader& reader, const NiHeader& header): NiProperty(reader, header) {
		flags = reader.read<uint16_t>();
		threshold = reader.read<uint8_t>();
	}
};