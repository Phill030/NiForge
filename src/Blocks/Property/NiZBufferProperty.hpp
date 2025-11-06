#pragma once
#include "NiProperty.hpp"
#include <cstdint>
#include "Reader.hpp"
#include "Core/NiHeader.hpp"

enum class NIFORGE_API ZBufferTestFunction : uint32_t
{
    Always = 0,
    Less = 1,
    Equal = 2,
    LessEqual = 3,
    Greater = 4,
    NotEqual = 5,
    GreaterEqual = 6,
    Never = 7
};

enum class NIFORGE_API ZBufferFlags : uint16_t
{
    Test = 0b00000001,
    Write = 0b00000010,
    Func = 0b00000100,
};

struct NIFORGE_API NiZBufferProperty : NiProperty
{
private:
    uint16_t flags = 0;

public:
    NiZBufferProperty(Reader& reader, const NiHeader& header): NiProperty(reader, header) {
		flags = reader.read<uint16_t>();
    }

    ZBufferFlags GetFlags() const {
        return static_cast<ZBufferFlags>(flags & 0b0000000000111111);
    }

    void SetFlags(ZBufferFlags value) {
        flags = static_cast<uint16_t>((flags & ~0b0000000000111111) | static_cast<uint16_t>(value));
    }

    ZBufferTestFunction GetTestFunc() const {
        return static_cast<ZBufferTestFunction>((flags >> 2) & 0b1111);
    }

    void SetTestFunc(ZBufferTestFunction value) {
        flags = static_cast<uint16_t>((flags & ~0b0000000000111100) | (static_cast<uint16_t>(value) << 2));
    }
};