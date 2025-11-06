#pragma once
#include "Reader.hpp"
#include "Blocks/NiObjectNet.hpp"
#include "Core/NiHeader.hpp"

// Abstract base class representing all rendering properties.
// Subclasses are attached to NiAVObjects to control their rendering.
struct NIFORGE_API NiProperty : NiObjectNet
{
	NiProperty(Reader& reader, const NiHeader& header) : NiObjectNet(reader, header) {}
	virtual ~NiProperty() = default;
};