#pragma once
#include <cstdint>

struct NIFORGE_API ByteColor4
{
	uint8_t r, g, b, a;
	ByteColor4() : r(0), g(0), b(0), a(0) {}
	ByteColor4(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}
};

struct NIFORGE_API Color4
{
	float r, g, b, a;
	Color4() : r(0.0f), g(0.0f), b(0.0f), a(0.0f) {}
	Color4(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
};