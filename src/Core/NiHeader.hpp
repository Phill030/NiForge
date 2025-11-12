#pragma once
#include "Reader.hpp"
#include "NiVersion.hpp"
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

struct NIFORGE_API NiHeader
{
	std::string header;
	NiVersion version;
	uint8_t endianess;
	uint32_t userVersion;
	uint32_t numBlocks;
	uint16_t numBlockTypes;
	std::vector<std::string> blockTypes;
	std::vector<uint16_t> blockTypeIndex;
	std::vector<uint32_t> blockSize;
	uint32_t maxStringLength;
	std::vector<std::string> strings;
	std::vector<uint32_t> groups;

	std::string getIndexString(Reader& reader) const {
		int32_t stringIndex = reader.read<int32_t>();

		if (stringIndex == 0xFFFFFFFF) {
			return "";
		}

		return strings[stringIndex];
	}

	NiHeader() = default;
	NiHeader(Reader& reader) {
		header = reader.readUntilNull();
		version = NiVersion(reader.read<uint32_t>());
		endianess = reader.read<uint8_t>();
		userVersion = reader.read<uint32_t>();
		numBlocks = reader.read<uint32_t>();
		numBlockTypes = reader.read<uint16_t>();

		blockTypes.reserve(numBlockTypes);
		for (uint16_t i = 0; i < numBlockTypes; i++) {
			blockTypes.emplace_back(reader.readString());
		}

		blockTypeIndex.reserve(numBlocks);
		for (uint32_t i = 0; i < numBlocks; i++) {
			blockTypeIndex.push_back(reader.read<uint16_t>());
		}

		blockSize.reserve(numBlocks);
		for (uint32_t i = 0; i < numBlocks; i++) {
			blockSize.push_back(reader.read<uint32_t>());
		}

		uint32_t numStrings = reader.read<uint32_t>();
		strings.reserve(numStrings);
		maxStringLength = reader.read<uint32_t>();
		for (uint32_t i = 0; i < numStrings; i++) {
			strings.emplace_back(reader.readString());
		}

		uint32_t numGroups = reader.read<uint32_t>();
		groups.reserve(numGroups);
		for (uint32_t i = 0; i < numGroups; i++) {
			groups.push_back(reader.read<uint32_t>());
		}
	}
};