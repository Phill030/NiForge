#pragma once
#include "Reader.hpp"
#include "NiSingleInterpController.hpp"

struct NIFORGE_API NiFloatInterpController : NiSingleInterpController
{
public:
	NiFloatInterpController(Reader& reader) : NiSingleInterpController(reader) {}
};