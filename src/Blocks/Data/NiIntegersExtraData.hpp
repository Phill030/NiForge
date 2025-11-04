#pragma once
#include "Core/NiHeader.hpp"
#include "Reader.hpp"
#include "NiExtraData.hpp"
#include <cstdint>
#include <vector>

struct NiIntegersExtraData : NiExtraData
{
public:
	uint32_t numIntegers;
	std::vector<uint32_t> data;

	NiIntegersExtraData(Reader& reader, const NiHeader& header) : NiExtraData(reader, header) {
		numIntegers = reader.read<uint32_t>();
		data.reserve(numIntegers);
		for (uint32_t i = 0; i < numIntegers; i++) {
			data.push_back(reader.read<uint32_t>());
		}
	}
};