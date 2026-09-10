#pragma once
#include "Core/NiHeader.hpp"
#include "Reader.hpp"
#include "NiProperty.hpp"
#include <cstdint>

enum class AlphaFunction : uint8_t
{
	ONE = 0,
	ZERO = 1,
	SRC_COLOR = 2,
	INV_SRC_COLOR = 3,
	DEST_COLOR = 4,
	INV_DEST_COLOR = 5,
	SRC_ALPHA = 6,
	INV_SRC_ALPHA = 7,
	DEST_ALPHA = 8,
	INV_DEST_ALPHA = 9,
	SRC_ALPHA_SATURATE = 10
};

enum class TestFunction : uint8_t
{
	ALWAYS = 0,
	LESS = 1,
	EQUAL = 2,
	LEQUAL = 3,
	GREATER = 4,
	NOTEQUAL = 5,
	GEQUAL = 6,
	NEVER = 7
};

struct NIFORGE_API NiAlphaProperty : NiProperty
{
public:
	uint16_t flags;
	uint8_t threshold;
	NiAlphaProperty(Reader& reader, const NiHeader& header): NiProperty(reader, header) {
		flags = reader.read<uint16_t>();
		threshold = reader.read<uint8_t>();
	}

	bool alphaBlend() const { return (flags & 0x0001) != 0; }
	
	AlphaFunction srcBlend() const { return static_cast<AlphaFunction>((flags >> 1) & 0x0F); }

	AlphaFunction destBlend() const { return static_cast<AlphaFunction>((flags >> 5) & 0x0F); }

	bool alphaTest() const { return (flags & 0x0200) != 0; }
	
	TestFunction testFunc() const { return static_cast<TestFunction>((flags >> 10) & 0x07); }
	
	bool noSorter() const { return (flags & 0x2000) != 0; }
	
	float testThreshold() const { return static_cast<float>(threshold) / 255.0f; }
};