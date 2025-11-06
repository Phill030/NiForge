#pragma once
#include <cstdint>
#include <vector>
#include "Key.hpp"

enum class NIFORGE_API KeyType : uint32_t
{
    LINEAR_KEY = 1, // Use linear interpolation.
    QUADRATIC_KEY = 2, // Use quadratic interpolation (stores forward/back tangents).
    TBC_KEY = 3, // Use Tension Bias Continuity interpolation (stores T, B, C values).
    XYZ_ROTATION_KEY = 4, // For rotation data — separate X, Y, Z keys instead of quaternions.
    CONST_KEY = 5  // Step function; used for visibility keys in NiBoolData.
};

template<typename T>
struct NIFORGE_API KeyGroup
{
    uint32_t numKeys;
    KeyType interpolation;
    std::vector<Key<T>> keys;
};
