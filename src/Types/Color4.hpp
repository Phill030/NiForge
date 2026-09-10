#pragma once
#include <cstdint>

struct NIFORGE_API Color4
{
	uint8_t r, g, b, a;
	constexpr Color4() : r(0), g(0), b(0), a(0) {}
	constexpr Color4(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}

	static constexpr Color4 BGRA(uint8_t b, uint8_t g, uint8_t r, uint8_t a) {
		return { b, g, r, a };
	}
};