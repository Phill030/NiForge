#pragma once
#include "../Core/NiHeader.hpp"
#include "../Reader.hpp"
#include "NiGeometry.hpp"

struct NiTriBasedGeom : NiGeometry
{
	NiTriBasedGeom(Reader& reader, const NiHeader& header) : NiGeometry(reader, header) {}
};