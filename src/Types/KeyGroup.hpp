#pragma once
#include <cstdint>
#include <vector>
#include "Key.hpp"
#include "Reader.hpp"

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
	// if numKeys is 0, interpolation is undefined
    KeyType interpolation;
    std::vector<Key<T>> keys;

    KeyGroup() : numKeys(0), interpolation(static_cast<KeyType>(0)), keys() {}

    static KeyGroup<T> ConstructFrom(Reader& reader) {
        KeyGroup<T> group; // Create a new instance to populate

        group.numKeys = reader.read<uint32_t>();

        if (group.numKeys > 0) {
            group.interpolation = static_cast<KeyType>(reader.read<uint32_t>());

            group.keys.reserve(group.numKeys);
            for (size_t i = 0; i < group.numKeys; i++) {
                Key<T> key;
                switch (group.interpolation) {
                    case KeyType::QUADRATIC_KEY:
                        key.time = reader.read<float>();
                        key.value = reader.read<T>();
                        key.forward = reader.read<T>();
                        key.backward = reader.read<T>();
                        break;
                    case KeyType::LINEAR_KEY:
                    case KeyType::CONST_KEY:
                        key.time = reader.read<float>();
                        key.value = reader.read<T>();
                        break;
                    default:
                        throw std::runtime_error("Unknown KeyType in KeyGroup: " + std::to_string(static_cast<uint32_t>(group.interpolation)));
                }
                group.keys.push_back(key);
            }
        }
        return group; // Return the fully constructed object
    }
};
