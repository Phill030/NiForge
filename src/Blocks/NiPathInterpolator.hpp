#pragma once
#include "NiKeyBasedInterpolator.hpp"
#include "Blocks/Data/NiPosData.hpp"
#include "Blocks/Data/NiFloatData.hpp"
#include "Types/Ref.hpp"
#include <cstdint>

enum class PathFlags : uint16_t
{
    NIPI_CVDataNeedsUpdate = 0x0001,
    NIPI_CurveTypeOpen = 0x0002,
    NIPI_AllowFlip = 0x0004,
    NIPI_Bank = 0x0008,
    NIPI_ConstantVelocity = 0x0010,
    NIPI_Follow = 0x0020,
    NIPI_Flip = 0x0040
};

struct NiPathInterpolator : NiKeyBasedInterpolator
{
    PathFlags flags;
    int32_t bankDir; // -1 = Negative, 1 = Positive
    float maxAngleBank; // Max angle in radians
    float smoothing;
    int16_t followAxis; // 0, 1, or 2 representing X, Y, or Z.
    Ref<NiPosData> pathData;
    Ref<NiFloatData> percentData;

    NiPathInterpolator(Reader& reader, const NiHeader& header) : NiKeyBasedInterpolator() {
        flags = static_cast<PathFlags>(reader.read<uint16_t>());
        bankDir = reader.read<int32_t>();
        maxAngleBank = reader.read<float>();
        smoothing = reader.read<float>();
        followAxis = reader.read<int16_t>();
        pathData = Ref<NiPosData>(reader);
        percentData = Ref<NiFloatData>(reader);
	}
};