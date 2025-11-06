#pragma once
#include "TexDesc.hpp"
#include <cstdint>
#include "Core/NiHeader.hpp"
#include "Reader.hpp"

struct NIFORGE_API ShaderTexDesc
{
	bool hasMap;
	TexDesc map;
	uint32_t mapId;

	ShaderTexDesc(Reader& reader, const NiHeader& header):
		hasMap(reader.read<bool>()),
		map(reader, header),
		mapId(reader.read<uint32_t>()) {}
};
