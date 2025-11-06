#pragma once
#include "Core/NiHeader.hpp"
#include "Types/Ref.hpp"
#include "Reader.hpp"
#include "Data/NiExtraData.hpp"
#include "NiObject.hpp"
#include <cstdint>
#include <string>
#include <vector>

// This class adds (N)ames, (E)xtra Data, and (T)ime controllers to NiObject.
struct NIFORGE_API NiObjectNet : NiObject
{
	std::string name;
	std::vector<Ref<NiExtraData>> extraData;
	int32_t controller; // TODO: Make Ref<NiTimeController>

	NiObjectNet(Reader& reader, const NiHeader& header) {
		name = header.getIndexString(reader);

		uint32_t numExtraData = reader.read<uint32_t>();
		extraData.reserve(numExtraData);
		for (int j = 0; j < numExtraData; j++) {
			extraData.push_back(Ref<NiExtraData>(reader));
		}

		controller = reader.read<int32_t>();
	}
};