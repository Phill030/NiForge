#pragma once
#include "NiInterpController.hpp"
#include "Types/Ref.hpp"
#include "Blocks/NiInterpolator.hpp"

struct NiSingleInterpController : NiInterpController
{
	Ref<NiInterpolator> interpolator;
	NiSingleInterpController(Reader& reader) : NiInterpController(reader),
		interpolator(Ref<NiInterpolator>(reader)) {}
};