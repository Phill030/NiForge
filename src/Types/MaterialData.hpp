#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include "../Reader.hpp"
#include "../Core/NiHeader.hpp"

struct MaterialData
{
public:
	uint32_t numMaterials;
	// The name of the material.
	std::vector<std::string> materialNames;
	// Extra data associated with the material. A value of -1 means the material is the default implementation.
	std::vector<int32_t> materialExtraData;
	// The index of the currently active material.
	int32_t activeMaterial;
	// Whether the materials for this object always needs to be updated before rendering with them.
	bool materialNeedsUpdate;

	MaterialData() = default;
	MaterialData(Reader& reader, const NiHeader& header) {
		numMaterials = reader.read<uint32_t>();
		materialNames.reserve(numMaterials);
		for (int i = 0; i < numMaterials; i++) {
			materialNames.push_back(header.strings[reader.read<int32_t>()]);
		}

		materialExtraData.reserve(numMaterials);
		for (int i = 0; i < numMaterials; i++) {
			materialExtraData.push_back(reader.read<int32_t>());
		}
		activeMaterial = reader.read<int32_t>();
		materialNeedsUpdate = reader.read<bool>();
	}
};