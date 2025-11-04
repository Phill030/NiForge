#pragma once
#include "Core/NiHeader.hpp"
#include "Reader.hpp"
#include "Types/Ref.hpp"
#include "NiInterpolator.hpp"
#include "NiInterpController.hpp"
#include <cstdint>
#include <string>
#include <vector>

struct NiMorphWeightsController : NiInterpController
{
	uint32_t count;
	uint32_t numInterpolators;
	std::vector<Ref<NiInterpolator>> interpolators;
	uint32_t numTargets;
	std::vector<std::string> targetNames;

	NiMorphWeightsController(Reader& reader, const NiHeader& header) : NiInterpController(reader) {
		count = reader.read<uint32_t>();
		numInterpolators = reader.read<uint32_t>();
		interpolators.reserve(numInterpolators);
		for (uint32_t i = 0; i < numInterpolators; i++) {
			interpolators.push_back(Ref<NiInterpolator>(reader));
		}
		numTargets = reader.read<uint32_t>();
		targetNames.reserve(numTargets);
		for (uint32_t i = 0; i < numTargets; i++) {
			std::string name = header.getIndexString(reader);
			targetNames.push_back(name);
		}
	}
};