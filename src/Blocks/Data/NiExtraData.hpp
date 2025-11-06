#pragma once
#include "Blocks/NiObject.hpp"
#include "Core/NiHeader.hpp"
#include "Reader.hpp"
#include <string>

struct NIFORGE_API NiExtraData : NiObject
{
	std::string name; // Name of this object
	NiExtraData(Reader& reader, const NiHeader& header) {
		name = header.getIndexString(reader);
	}
};