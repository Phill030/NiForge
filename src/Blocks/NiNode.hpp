#pragma once
#include "Core/NiHeader.hpp"
#include "Reader.hpp"
#include "Types/Ref.hpp"
#include "NiAvObject.hpp"
#include "NiDynamicEffect.hpp"
#include <cstdint>
#include <vector>

struct NIFORGE_API NiNode : NiAvObject
{
public:
	uint32_t numChildren;
	std::vector<Ref<NiAvObject>> children;
	uint32_t numEffects;
	std::vector<Ref<NiDynamicEffect>> effects;

	NiNode(Reader& reader, const NiHeader& header) : NiAvObject(reader, header)  {
		numChildren = reader.read<uint32_t>();
		children.reserve(numChildren);
		for (uint32_t j = 0; j < numChildren; j++) {
			children.emplace_back(reader);
		}

		numEffects = reader.read<uint32_t>();
		effects.reserve(numEffects);
		for (uint32_t j = 0; j < numEffects; j++) {
			effects.emplace_back(reader);
		}
	}
};
