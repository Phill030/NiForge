#pragma once
#include "NiTriBasedGeom.hpp"
#include "Core/NiHeader.hpp"
#include "Reader.hpp"

struct NIFORGE_API NiTriShape : NiTriBasedGeom
{
	NiTriShape(Reader& reader, const NiHeader& header) : NiTriBasedGeom(reader, header) {}
};