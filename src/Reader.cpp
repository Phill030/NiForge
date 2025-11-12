#include "Reader.hpp"
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

Reader::Reader(const std::vector<uint8_t>& data) : data(&data), pos(0) {}

std::string Reader::readString(size_t length) {
    if (pos + length > data->size())
        throw std::out_of_range("Read past end of buffer");

    std::string s(reinterpret_cast<const char*>(&(*data)[pos]), length);
    pos += length;
    return s;
}

std::string Reader::readString() {
    uint32_t length = read<uint32_t>();
    return readString(length);
}

std::string Reader::readUntilNull() {
    size_t start = pos;
    while (pos < data->size() && (*data)[pos] != 0x0A) {
        pos++;
    }
    if (pos >= data->size())
        throw std::out_of_range("Null terminator not found");
    std::string s(reinterpret_cast<const char*>(&(*data)[start]), pos - start);
    pos++;
    return s;
}


std::vector<uint8_t> Reader::read(uint32_t length) {
    if (pos + length > data->size())
        throw std::out_of_range("Read past end of buffer");
    std::vector<uint8_t> buf(data->data() + pos, data->data() + pos + length);
    pos += length;
    return buf;
}