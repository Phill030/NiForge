#pragma once
#include "NiTimeController.hpp"
#include "Reader.hpp"

struct NiInterpController : NiTimeController
{
	NiInterpController(Reader& reader) : NiTimeController(reader) {}
};