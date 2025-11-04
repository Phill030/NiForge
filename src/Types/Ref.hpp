#pragma once

#include "Blocks/NiObject.hpp"
#include "Reader.hpp"
#include <cstdint>
#include <type_traits>

// Forward declaration
struct NiFile;

template <typename T>
struct Ref
{
    static_assert(std::is_base_of_v<NiObject, T>, "T must derive from NiObject");
    int32_t value;

    explicit Ref(Reader& reader) {
        value = reader.read<int32_t>();
    }

    // Declare but don't define
    T* getReference(const NiFile& file) const;

    bool hasReference() const { return value != -1; }
};