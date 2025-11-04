#pragma once
#include "Reader.hpp"
#include "NiVersion.hpp"
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

struct NiHeader
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

		if(stringIndex < 0 || static_cast<size_t>(stringIndex) > strings.size())
			throw std::out_of_range("String index out of range");

		if (stringIndex == 0xFFFFFFFF) {
			return "";
		}

		return strings[stringIndex];
	}

	NiHeader(Reader& reader) {
		header = reader.readUntilNull();
		version = NiVersion(reader.read<uint32_t>());
		endianess = reader.read<uint8_t>();
		userVersion = reader.read<uint32_t>();
		numBlocks = reader.read<uint32_t>();
		numBlockTypes = reader.read<uint16_t>();

		blockTypes.reserve(numBlockTypes);
		for (int i = 0; i < numBlockTypes; i++) {
			std::string name = reader.readString();
			blockTypes.push_back(name);
		}

		blockTypeIndex.reserve(numBlocks);
		for (int i = 0; i < numBlocks; i++) {
			blockTypeIndex.push_back(reader.read<uint16_t>());
		}

		blockSize.reserve(numBlocks);
		for (int i = 0; i < numBlocks; i++) {
			blockSize.push_back(reader.read<uint32_t>());
		}

		strings.reserve(reader.read<uint32_t>());
		maxStringLength = reader.read<uint32_t>();
		for (int i = 0; i < strings.capacity(); i++) {
			strings.push_back(reader.readString());
		}

		groups.reserve(reader.read<uint32_t>());
		for (int i = 0; i < groups.capacity(); i++) {
			groups.push_back(reader.read<uint32_t>());
		}
	}
};