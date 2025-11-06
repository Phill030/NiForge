#pragma once
#include "Core/NiHeader.hpp"
#include "Reader.hpp"
#include "NiAvObject.hpp"
#include <cstdint>
#include <vector>

// Abstract base class for dynamic effects such as NiLights or projected texture effects. 
struct NIFORGE_API NiDynamicEffect : NiAvObject
{
	bool switchState; // If true, then the dynamic effect is applied to affected nodes during rendering.
	uint32_t numAffectedNodes;
	std::vector<uint32_t> affectedNodes; // If a node appears in this list, then its entire subtree will be affected by the effect.

	NiDynamicEffect(Reader& reader, const NiHeader& header) : NiAvObject(reader, header) {
		switchState = reader.read<bool>();
		numAffectedNodes = reader.read<uint32_t>();
		affectedNodes.reserve(numAffectedNodes);
		for (uint32_t i = 0; i < numAffectedNodes; i++) {
			affectedNodes.push_back(reader.read<uint32_t>());
		}
	}

};