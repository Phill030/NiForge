#pragma once
#include "DataStreamData.hpp"
#include <cstdint>
#include <vector>

struct DataStreamIndex : DataStreamData
{
	using value_type = uint16_t;
	std::vector<uint16_t> values;
};