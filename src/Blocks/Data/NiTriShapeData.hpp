#pragma once
#include "Core/NiHeader.hpp"
#include "Reader.hpp"
#include "Types/MatchGroup.hpp"
#include "Types/Triangle.hpp"
#include "NiTriBasedGeomData.hpp"
#include <cstdint>
#include <vector>

struct NIFORGE_API NiTriShapeData : NiTriBasedGeomData
{
    uint32_t numTrianglePoints;

    bool hasTriangles;
    std::vector<Triangle> triangles;

    uint16_t numMatchGroups;
    std::vector<MatchGroup> matchGroups;
    NiTriShapeData(Reader& reader, const NiHeader& header) : NiTriBasedGeomData(reader, header) {
        numTrianglePoints = reader.read<uint32_t>();

        hasTriangles = reader.read<bool>();
        if (hasTriangles) {
            triangles.reserve(numTriangles);
            for (int i = 0; i < numTriangles; i++) {
                triangles.push_back(reader.read<Triangle>());
            }
        }

        numMatchGroups = reader.read<uint16_t>();
        matchGroups.reserve(numMatchGroups);
        for (size_t i = 0; i < numMatchGroups; i++) {
            matchGroups.push_back(reader.read<MatchGroup>());
        }
    }
};