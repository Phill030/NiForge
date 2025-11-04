#pragma once
#include "Core/NiHeader.hpp"
#include "Reader.hpp"
#include "NiObject.hpp"
#include <string>

struct NiExtraData : NiObject
{
	std::string name; // Name of this object
	NiExtraData(Reader& reader, const NiHeader& header) {
		name = header.getIndexString(reader);
	}
};