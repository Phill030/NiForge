#pragma once
#include "../../Core/NiHeader.hpp"
#include "../../Reader.hpp"
#include "NiProperty.hpp"
#include <cstdint>

struct NiSpecularProperty : NiProperty
{
	uint16_t flags;
	NiSpecularProperty(Reader& reader, const NiHeader& header) : NiProperty(reader, header) {
		flags = reader.read<uint16_t>();
	}
};