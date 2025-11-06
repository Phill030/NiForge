#pragma once
#include "Blocks/NiObject.hpp"
#include "Core/NiHeader.hpp"
#include "Reader.hpp"
#include "Types/Key.hpp"
#include "Types/KeyGroup.hpp"
#include <cstdint>
#include <stdexcept>
#include <string>

struct NIFORGE_API NiBoolData : NiObject
{
	KeyGroup<uint8_t> data;

	NiBoolData(Reader& reader, NiHeader& header) : NiObject() {
		data.numKeys = reader.read<uint32_t>();
		data.interpolation = static_cast<KeyType>(reader.read<uint32_t>());

		data.keys.reserve(data.numKeys);
		for (size_t i = 0; i < data.numKeys; i++) {
			Key<uint8_t> key;

			switch (data.interpolation) {
				case KeyType::CONST_KEY:
					key.time = reader.read<float>();
					key.value = reader.read<uint8_t>();
					break;
				default:
					throw std::runtime_error("Unknown KeyType in NiBoolData: " + std::to_string(static_cast<uint32_t>(data.interpolation)));
			}
		}

	}
};