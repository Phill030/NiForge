#pragma once
#include "Blocks/NiObject.hpp"
#include "Types/Vector3.hpp"
#include "Types/KeyGroup.hpp"

struct NiPosData : NiObject
{
	KeyGroup<Vector3> data;
	NiPosData(Reader& reader, const NiHeader& header) {
		data = KeyGroup<Vector3>::ConstructFrom(reader);
	}
};