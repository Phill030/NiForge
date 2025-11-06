#include "gtest/gtest.h"
#include "Reader.hpp"
#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "Core/NiFile.hpp"

TEST(ReaderTest, CanBeCreated) {
    Reader reader;
    SUCCEED();
}

TEST(ReadFileTest, CanReadFile) {
    std::string testFilePath = "data/WC_Z06_Unicorn_Way.nif";

    std::ifstream file(testFilePath, std::ios::binary);
    if (!file.is_open())
        throw std::runtime_error("Failed to open file: " + testFilePath);

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(size);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), size))
        throw std::runtime_error("Failed to read file: " + testFilePath);

    SUCCEED();
}

TEST(ParseFile, CanParseFile) {
    std::string testFilePath = "data/WC_Z06_Unicorn_Way.nif";

    std::ifstream file(testFilePath, std::ios::binary);
    if (!file.is_open())
        throw std::runtime_error("Failed to open file: " + testFilePath);

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(size);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), size))
        throw std::runtime_error("Failed to read file: " + testFilePath);

    NiFile niFile(buffer);

    SUCCEED();
}

TEST(ParseFile, CanParseFile2) {
    std::string testFilePath = "data/WC_Z00_Hub.nif";

    std::ifstream file(testFilePath, std::ios::binary);
    if (!file.is_open())
        throw std::runtime_error("Failed to open file: " + testFilePath);

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(size);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), size))
        throw std::runtime_error("Failed to read file: " + testFilePath);

    NiFile niFile(buffer);

    SUCCEED();
}


TEST(ParseFile, CanParseFile3) {
    std::string testFilePath = "data/WC_Unicorn_DSigns_A01_KH.nif";

    std::ifstream file(testFilePath, std::ios::binary);
    if (!file.is_open())
        throw std::runtime_error("Failed to open file: " + testFilePath);

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(size);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), size))
        throw std::runtime_error("Failed to read file: " + testFilePath);

    NiFile niFile(buffer);

    SUCCEED();
}
