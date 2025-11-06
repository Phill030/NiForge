#pragma once
#include "DataStreamData.hpp"
#include "Types/Vector3.hpp"
#include <vector>

struct NIFORGE_API DataStreamNormal : DataStreamData
{
	using value_type = Vector3;
	std::vector<Vector3> values;
};