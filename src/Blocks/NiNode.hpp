#pragma once
#include "Core/NiHeader.hpp"
#include "Reader.hpp"
#include "Types/Ref.hpp"
#include "NiAvObject.hpp"
#include "NiDynamicEffect.hpp"
#include <cstdint>
#include <vector>

struct NiNode : NiAvObject
{
public:
	uint32_t numChildren;
	std::vector<Ref<NiAvObject>> children;
	uint32_t numEffects;
	std::vector<Ref<NiDynamicEffect>> effects;

	NiNode(Reader& reader, const NiHeader& header) : NiAvObject(reader, header)  {
		numChildren = reader.read<uint32_t>();
		children.reserve(numChildren);
		for (int j = 0; j < numChildren; j++) {
			children.push_back(Ref<NiAvObject>(reader));
		}

		numEffects = reader.read<uint32_t>();
		effects.reserve(numEffects);
		for (int j = 0; j < numEffects; j++) {
			effects.push_back(Ref<NiDynamicEffect>(reader));
		}
	}
};
