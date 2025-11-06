#pragma once
#include "Core/NiHeader.hpp"
#include "Reader.hpp"
#include "NiExtraData.hpp"
#include <string>

struct NIFORGE_API NiStringExtraData : NiExtraData
{
	std::string stringData; // The String
	NiStringExtraData(Reader& reader, const NiHeader& header) : NiExtraData(reader, header) {
		stringData = header.getIndexString(reader);
	}
};