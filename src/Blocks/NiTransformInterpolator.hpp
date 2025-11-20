#pragma once
#include "NiKeyBasedInterpolator.hpp"
#include "Types/NiQuatTransform.hpp"
#include "Data/NiTransformData.hpp"
#include "Types/Ref.hpp"

struct NIFORGE_API NiTransformInterpolator : NiKeyBasedInterpolator
{
	NiQuatTransform transform;
	Ref<NiTransformData> data;

	NiTransformInterpolator(Reader& reader, const NiHeader& header) :
		NiKeyBasedInterpolator(), transform(reader.read<NiQuatTransform>()), data(reader) {}
};