#pragma once
#include "Types/Vector3.hpp"
#include "Types/Quaternion.hpp"

struct NiQuatTransform
{
	Vector3 translation;
	Quaternion rotation;
	float scale;

	NiQuatTransform() : translation(), rotation(), scale(1.0f) {}
	NiQuatTransform(const Vector3& translation, const Quaternion& rotation, float scale)
		: translation(translation), rotation(rotation), scale(scale) {}
};