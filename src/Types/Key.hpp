#pragma once
#include "Types/TBC.hpp"

template<typename T>
struct NIFORGE_API Key
{
	float time;
	T value;
	T forward;
	T backward;
	TBC tbc;

	Key() : time(0.0f), value(T{}), forward(T{}), backward(T{}), tbc(TBC{}) {}

	Key(float t, T v, T f, T b) :
		time(t), value(v), forward(f), backward(b), tbc(TBC{}) {
	}

	Key(float t, T v) :
		time(t), value(v), forward(T{}), backward(T{}), tbc(TBC{}) {
	}

	Key(float t, T v, TBC tbc) :
		time(t), value(v), forward(T{}), backward(T{}), tbc(tbc) {
	}
};