#pragma once
#include "NiKeyframeController.hpp"
#include "Reader.hpp"
#include "NiHeader.hpp"

struct NIFORGE_API NiTransformController : NiKeyframeController
{
	NiTransformController(Reader& reader, const NiHeader& header) : NiKeyframeController(reader) {

	}
};