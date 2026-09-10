#pragma once
#include "Core/NiHeader.hpp"
#include "NiNode.hpp"
#include "Reader.hpp"
#include <cstdint>

enum class SortingMode : uint32_t
{
	// Inherit. Acts identical to NiNode.
	SORTING_INHERIT = 0,
	// Disables sort on all geometry under this node.
	SORTING_OFF = 1
};

struct NIFORGE_API NiSortAdjustNode : NiNode
{
public: 
	SortingMode sortingMode;

	NiSortAdjustNode(Reader& reader, const NiHeader& header) : NiNode(reader, header) {
		sortingMode = static_cast<SortingMode>(reader.read<uint32_t>());
	}
};