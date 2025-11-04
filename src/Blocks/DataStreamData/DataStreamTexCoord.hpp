#pragma once
#include "DataStreamData.hpp"
#include "Types/TexCoord.hpp"
#include <vector>

struct DataStreamTexCoord : DataStreamData
{
	using value_type = TexCoord;
	std::vector<TexCoord> values;
};