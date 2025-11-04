#pragma once
#include "Types/Vector3.hpp"
#include "Core/NiHeader.hpp"
#include "Reader.hpp"

struct NiBound
{
	Vector3 center; // The sphere's center.
	float radius; // The sphere's radius.

	NiBound() = default;
	NiBound(Reader& reader, const NiHeader& header) {
		center = reader.read<Vector3>();
		radius = reader.read<float>();
	}
};