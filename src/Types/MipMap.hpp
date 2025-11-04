#pragma once
#include <cstdint>

struct MipMap
{
	uint32_t width, height, offset;
	MipMap() : width(0), height(0), offset(0) {}
	MipMap(uint32_t width, uint32_t height, uint32_t offset) : width(width), height(height), offset(offset) {}
};