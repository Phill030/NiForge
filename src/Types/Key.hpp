#pragma once

template<typename T>
struct NIFORGE_API Key
{
	float time;
	T value;
	T forward;
	T backward;
	
	Key() : time(0.0f), value(T{}), forward(T{}), backward(T{}) {}

	Key(float t, T v, T f, T b) :
		time(t), value(v), forward(f), backward(b) {}

	Key(float t, T v) :
		time(t), value(v), forward(T{}), backward(T{}) {
	}
};