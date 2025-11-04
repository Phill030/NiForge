#pragma once
#include "NiObjectNet.hpp"
#include "Core/NiHeader.hpp"
#include "Reader.hpp"
#include "Types/Matrix.hpp"
#include "Types/Vector3.hpp"
#include <cstdint>
#include <vector>


struct NiAvObject : NiObjectNet
{
	uint16_t flags;
	Vector3 translation;
	Matrix<3, 3> rotation;
	float scale;
	uint32_t numProperties;
	std::vector<uint32_t> properties;
	int32_t collisionObject;

	NiAvObject(Reader& reader, const NiHeader& header) : NiObjectNet(reader, header) {
		flags = reader.read<uint16_t>();
		translation = reader.read<Vector3>();
		rotation = reader.readMatrix<3, 3>();
		scale = reader.read<float>();

		numProperties = reader.read<uint32_t>();

		properties.reserve(numProperties);
		for (int j = 0; j < numProperties; j++) {
			properties.push_back(reader.read<uint32_t>());
		}

		collisionObject = reader.read<int32_t>();
	}
};