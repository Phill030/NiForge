#pragma once
#include <cstdint>

struct NIFORGE_API NiVersion
{
	uint8_t major;
	uint8_t minor;
	uint8_t patch;
	uint8_t build;

	NiVersion() :
		major(0),
		minor(0),
		patch(0),
		build(0) {}

	NiVersion(uint8_t major, uint8_t minor, uint8_t patch, uint8_t build) : 
		major(major),
		minor(minor),
		patch(patch),
		build(build) {}

	NiVersion(uint32_t version) {
		major = (version >> 24) & 0xFF;
		minor = (version >> 16) & 0xFF;
		patch = (version >> 8) & 0xFF;
		build = version & 0xFF;
	}

	bool operator==(const NiVersion& other) const {
		return major == other.major &&
			minor == other.minor &&
			patch == other.patch &&
			build == other.build;
	}

	bool operator!=(const NiVersion& other) const {
		return !(*this == other);
	}

	bool operator<(const NiVersion& other) const {
		if (major != other.major)
			return major < other.major;

		if (minor != other.minor)
			return minor < other.minor;

		if (patch != other.patch)
			return patch < other.patch;

		return build < other.build;
	}

	bool operator>(const NiVersion& other) const {
		return other < *this;
	}

	bool operator<=(const NiVersion& other) const {
		return !(*this > other);
	}

	bool operator>=(const NiVersion& other) const {
		return !(*this < other);
	}
};