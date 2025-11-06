#pragma once
#include "Core/NiHeader.hpp"
#include "Reader.hpp"
#include "NiGeometryData.hpp"
#include <cstdint>

struct NIFORGE_API NiTriBasedGeomData : NiGeometryData
{
	uint16_t numTriangles;

	NiTriBasedGeomData(Reader& reader, const NiHeader& header) : NiGeometryData(reader, header) {
		numTriangles = reader.read<uint16_t>();
	}
};