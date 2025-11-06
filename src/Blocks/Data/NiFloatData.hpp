#pragma once
#include "Blocks/NiObject.hpp"
#include "Core/NiHeader.hpp"
#include "Reader.hpp"
#include "Types/Key.hpp"
#include "Types/KeyGroup.hpp"
#include <cstdint>
#include <stdexcept>
#include <string>

struct NiFloatData : NiObject
{
public:
	KeyGroup<float> data;
	NiFloatData(Reader& reader, const NiHeader& header) : NiObject() {
		data.numKeys = reader.read<uint32_t>();
		data.interpolation = static_cast<KeyType>(reader.read<uint32_t>());

		data.keys.reserve(data.numKeys);
		for (size_t i = 0; i < data.numKeys; i++) {
			Key<float> key;

			switch (data.interpolation) {
				case KeyType::QUADRATIC_KEY:
					key.time = reader.read<float>();
					key.value = reader.read<float>();
					key.forward = reader.read<float>();
					key.backward = reader.read<float>();
					break;
				case KeyType::LINEAR_KEY:
				case KeyType::CONST_KEY:
					key.time = reader.read<float>();
					key.value = reader.read<float>();
					break;

				default:
					throw std::runtime_error("Unknown KeyType in NiFloatData: " + std::to_string(static_cast<uint32_t>(data.interpolation)));
			}

			data.keys.push_back(key);
		}
	}
};