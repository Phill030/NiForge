#pragma once
#include "../../Reader.hpp"
#include "NiSingleInterpController.hpp"

struct NiFloatInterpController : NiSingleInterpController
{
public:
	NiFloatInterpController(Reader& reader) : NiSingleInterpController(reader) {}
};