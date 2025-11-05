#pragma once
#include <vector>
#include <string>
#include "Types/Vector3.hpp"
#include "Types/Color3.hpp"
#include "Types/Color4.hpp"
#include "Types/Matrix.hpp"
#include "Types/Triangle.hpp"
#include "Types/TexCoord.hpp"
#include "Types/MipMap.hpp"
#include "Types/MatchGroup.hpp"
#include "Defines.hpp"


struct NIFORGE_API Reader
{
	Reader() = default;
	explicit Reader(const std::vector<uint8_t>& data);

	template<typename T>
	T read();

	template<std::size_t N, std::size_t M, typename T = float>
	Matrix<N, M, T> readMatrix();

	std::vector<uint8_t> read(uint32_t length);
	std::string readString(size_t length);
	std::string readString();
	std::string readUntilNull();

	void seek(size_t newPos) { pos = newPos; }
	size_t tell() const noexcept { return pos; }

private:
	const std::vector<uint8_t>* data;
	size_t pos;

};


template<typename T>
T Reader::read() {
    if (pos + sizeof(T) > data->size())
        throw std::out_of_range("Read past end of buffer");

    T value;
    std::memcpy(&value, data->data() + pos, sizeof(T));
    pos += sizeof(T);
    return value;
}

template<std::size_t N, std::size_t M, typename T>
Matrix<N, M, T> Reader::readMatrix() {
	Matrix<N, M, T> mat;
	for (std::size_t i = 0; i < N; ++i) {
		for (std::size_t j = 0; j < M; ++j) {
			mat.m[i][j] = read<T>();
		}
	}
	return mat;
}

template<> inline Vector3 Reader::read<Vector3>() {
	return { read<float>(), read<float>(), read<float>() };
}

template<> inline Color3 Reader::read<Color3>() {
	return { read<float>(), read<float>(), read<float>() };
}

template<> inline Color4 Reader::read<Color4>() {
	return { read<uint8_t>(), read<uint8_t>(), read<uint8_t>(), read<uint8_t>() };
}

template<> inline Triangle Reader::read<Triangle>() {
	return { read<uint16_t>(), read<uint16_t>(), read<uint16_t>() };
}

template<> inline TexCoord Reader::read<TexCoord>() {
	return { read<float>(), read<float>() };
}

template<> inline MipMap Reader::read<MipMap>() {
	return { read<uint32_t>(), read<uint32_t>(), read<uint32_t>() };
}

template<> inline MatchGroup Reader::read<MatchGroup>() {
	uint16_t numVertices = read<uint16_t>();
	std::vector<uint16_t> vertexIndices;

	vertexIndices.reserve(numVertices);
	for (uint16_t i = 0; i < numVertices; i++) {
		vertexIndices.push_back(read<uint16_t>());
	}

	return MatchGroup(numVertices, vertexIndices);
}