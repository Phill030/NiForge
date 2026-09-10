#pragma once
#include "DataStreamData.hpp"
#include "Types/ByteColor4.hpp"
#include <vector>

struct NIFORGE_API DataStreamColor : DataStreamData
{
	using value_type = ByteColor4;
	std::vector<ByteColor4> values;
};