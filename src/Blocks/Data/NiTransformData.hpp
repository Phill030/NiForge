#pragma once
#include "Blocks/Data/NiKeyframeData.hpp"
#include "Reader.hpp"
#include "NiHeader.hpp"

struct NIFORGE_API NiTransformData : NiKeyframeData
{
	NiTransformData(Reader& reader, const NiHeader& header) : NiKeyframeData(reader, header) {}
};