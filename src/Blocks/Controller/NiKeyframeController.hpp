#pragma once
#include "NiSingleInterpController.hpp"

struct NIFORGE_API NiKeyframeController : NiSingleInterpController
{
	NiKeyframeController(Reader& reader) : NiSingleInterpController(reader) {}
};