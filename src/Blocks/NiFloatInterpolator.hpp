#pragma once
#include "NiKeyBasedInterpolator.hpp"
#include "Reader.hpp"
#include "Core/NiHeader.hpp"
#include "Data/NiFloatData.hpp"
#include "Types/Ref.hpp"

struct NIFORGE_API NiFloatInterpolator : NiKeyBasedInterpolator
{
public:
	float value; // Pose value if lacking NiFloatData.
	Ref<NiFloatData> data;
	NiFloatInterpolator(Reader& reader, const NiHeader& header) : NiKeyBasedInterpolator(),
		value(reader.read<float>()),
		data(Ref<NiFloatData>(reader)) {}
};