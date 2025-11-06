#pragma once
#include "DataStreamData.hpp"
#include <cstdint>
#include <vector>

struct NIFORGE_API DataStreamIndex : DataStreamData
{
	using value_type = uint16_t;
	std::vector<uint16_t> values;
};