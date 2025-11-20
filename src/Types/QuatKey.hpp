#pragma once
#include "Types/TBC.hpp"

template <typename T>
struct QuatKey
{
	float time;
	T value;
	TBC tbc;

	QuatKey() : time(0.0f), value(), tbc(TBC{}) {}
	QuatKey(float time, const T& value, const TBC& tbc) : time(time), value(value), tbc(tbc) {}
};