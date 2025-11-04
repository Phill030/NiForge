#pragma once
#include "DataStreamData.hpp"
#include "Types/Color4.hpp"
#include <vector>

struct DataStreamColor : DataStreamData
{
	using value_type = Color4;
	std::vector<Color4> values;
};