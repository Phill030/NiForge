#pragma once
#include "NiSingleInterpController.hpp"

struct NiKeyframeController : NiSingleInterpController
{
	NiKeyframeController(Reader& reader) : NiSingleInterpController(reader) {}
};