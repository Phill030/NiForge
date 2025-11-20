#pragma once
#include "NiKeyframeController.hpp"
#include "Reader.hpp"
#include "NiHeader.hpp"

struct NiTransformController : NiKeyframeController
{
	NiTransformController(Reader& reader, const NiHeader& header) : NiKeyframeController(reader) {

	}
};