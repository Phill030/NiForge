#pragma once
#include "NiInterpController.hpp"
#include "Types/Ref.hpp"
#include "Blocks/NiInterpolator.hpp"
#include "Reader.hpp"

struct NIFORGE_API NiSingleInterpController : NiInterpController
{
	Ref<NiInterpolator> interpolator;
	NiSingleInterpController(Reader& reader) : NiInterpController(reader),
		interpolator(Ref<NiInterpolator>(reader)) {}
};