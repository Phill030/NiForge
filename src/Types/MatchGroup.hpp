#pragma once
#include <cstdint>
#include <vector>

struct MatchGroup
{
	uint16_t numVertices;
	std::vector<uint16_t> vertexIndices;

	MatchGroup(uint16_t numVertices, std::vector<uint16_t> vertexIndices) : numVertices(numVertices), vertexIndices(std::move(vertexIndices)) {}
};