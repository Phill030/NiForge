#pragma once
#include "Blocks/NiObject.hpp"
#include "Core/NiHeader.hpp"
#include "Defines.hpp"
#include "Reader.hpp"
#include "Types/Key.hpp"
#include "Types/KeyGroup.hpp"
#include "Types/Vector3.hpp"
#include "Types/QuatKey.hpp"
#include "Types/Quaternion.hpp"
#include "Types/TBC.hpp"
#include <array>
#include <cstdint>
#include <vector>
#include <optional>
#include <stdexcept>

struct NIFORGE_API NiKeyframeData : NiObject
{
	// The number of quaternion rotation keys. If the rotation type is XYZ (type 4) then this *must* be set to 1, and in this case the actual number of keys is stored in the XYZ Rotations field.
	uint32_t numRotationKeys;

	std::optional<std::vector<QuatKey<Quaternion>>> quaternionKeys;

	// The type of interpolation to use for rotation. Can also be 4 to indicate that separate X, Y, and Z values are used for the rotation instead of Quaternions.
	std::optional<KeyType> rotationType;

	// Individual arrays of keys for rotating X, Y, and Z individually.
	std::array<KeyGroup<float>, 3> xyzRotations;

	// Translation keys.
	KeyGroup<Vector3> translations;

	// Scale keys.
	KeyGroup<float> scales;

	NiKeyframeData(Reader& reader, const NiHeader& header) {
		numRotationKeys = reader.read<uint32_t>();

		// if numRotationkeys is < 1, then there is no rotationType & there is a QuatKey
		if (numRotationKeys < 1) {
			/*QuatKey<Quaternion> key;
			key.time = reader.read<float>();
			key.value = reader.read<Quaternion>();
			key.tbc = TBC{ reader.read<float>(), reader.read<float>(), reader.read<float>() };*/
		}
		else {
			rotationType = static_cast<KeyType>(reader.read<uint32_t>());

			// If the rotation type is XYZ (type 4) then this *must* be set to 1, 
			// and in this case the actual number of keys is stored in the XYZ Rotations field.
			if (static_cast<uint32_t>(rotationType.value()) == 4)
				numRotationKeys = 1;

			for (uint32_t i = 0; i < xyzRotations.size(); i++) {
				xyzRotations[i] = KeyGroup<float>().ConstructFrom(reader);
			}
		}
		
		translations = KeyGroup<Vector3>().ConstructFrom(reader);
		scales = KeyGroup<float>().ConstructFrom(reader);
	}
};