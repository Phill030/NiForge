#pragma once
#include "NiTriBasedGeom.hpp"
#include "../Core/NiHeader.hpp"
#include "../Reader.hpp"

struct NiTriShape : NiTriBasedGeom
{
	NiTriShape(Reader& reader, const NiHeader& header) : NiTriBasedGeom(reader, header) {}
};