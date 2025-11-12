#include "Blocks/Controller/NiMorphWeightsController.hpp"
#include "Blocks/Controller/NiTextureTransformController.hpp"
#include "Blocks/Data/NiBooleanExtraData.hpp"
#include "Blocks/Data/NiFloatData.hpp"
#include "Blocks/Data/NiIntegerExtraData.hpp"
#include "Blocks/Data/NiIntegersExtraData.hpp"
#include "Blocks/Data/NiPixelData.hpp"
#include "Blocks/Data/NiStringExtraData.hpp"
#include "Blocks/Data/NiTriShapeData.hpp"
#include "Blocks/DataStreamData/DataStreamColor.hpp"
#include "Blocks/DataStreamData/DataStreamData.hpp"
#include "Blocks/DataStreamData/DataStreamIndex.hpp"
#include "Blocks/DataStreamData/DataStreamNormal.hpp"
#include "Blocks/DataStreamData/DataStreamPosition.hpp"
#include "Blocks/DataStreamData/DataStreamTexCoord.hpp"
#include "Blocks/NiBillboardNode.hpp"
#include "Blocks/NiDataStream.hpp"
#include "Blocks/NiFloatInterpolator.hpp"
#include "Blocks/NiMesh.hpp"
#include "Blocks/NiNode.hpp"
#include "Blocks/NiObject.hpp"
#include "Blocks/NiSourceTexture.hpp"
#include "Blocks/NiTriShape.hpp"
#include "Blocks/Property/NiAlphaProperty.hpp"
#include "Blocks/Property/NiMaterialProperty.hpp"
#include "Blocks/Property/NiSpecularProperty.hpp"
#include "Blocks/Property/NiStencilProperty.hpp"
#include "Blocks/Property/NiTexturingProperty.hpp"
#include "Blocks/Property/NiVertexColorProperty.hpp"
#include "Blocks/Property/NiZBufferProperty.hpp"
#include "NiFile.hpp"
#include "NiHeader.hpp"
#include "Reader.hpp"
#include "Types/Color4.hpp"
#include "Types/TexCoord.hpp"
#include "Types/Vector3.hpp"
#include "Blocks/Data/NiBoolData.hpp"
#include <cctype>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <functional>
#include <ios>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

template<typename T>
void addStreamValue(std::vector<std::unique_ptr<DataStreamData>>& streams, const typename T::value_type& value) {
    for (auto& stream : streams) {
        if (auto typed_stream = dynamic_cast<T*>(stream.get())) {
            typed_stream->values.push_back(value);
            return;
        }
    }

    auto new_stream = std::make_unique<T>();
    new_stream->values.push_back(value);
    streams.push_back(std::move(new_stream));
}

std::string_view getReadableText(const std::string& input) {
    size_t len = 0;
    for (unsigned char c : input) {
        if (!isprint(c))
            break;
        len++;
    }
    return std::string_view(input.data(), len);
}

static const std::unordered_map<std::string_view, std::function<std::shared_ptr<NiObject>(Reader&, NiHeader&)>> factories = {
            {"NiNode", [](Reader& r, NiHeader& h) { return std::make_shared<NiNode>(r, h); }},
            {"NiZBufferProperty", [](Reader& r, NiHeader& h) { return std::make_shared<NiZBufferProperty>(r, h); }},
            {"NiVertexColorProperty", [](Reader& r, NiHeader& h) { return std::make_shared<NiVertexColorProperty>(r, h); }},
            {"NiMesh", [](Reader& r, NiHeader& h) { return std::make_shared<NiMesh>(r, h); }},
            {"NiTexturingProperty", [](Reader& r, NiHeader& h) { return std::make_shared<NiTexturingProperty>(r, h); }},
            {"NiStringExtraData", [](Reader& r, NiHeader& h) { return std::make_shared<NiStringExtraData>(r, h); }},
            {"NiMaterialProperty", [](Reader& r, NiHeader& h) { return std::make_shared<NiMaterialProperty>(r, h); }},
            {"NiDataStream", [](Reader& r, NiHeader& h) { return std::make_shared<NiDataStream>(r, h); }},
            {"NiSourceTexture", [](Reader& r, NiHeader& h) { return std::make_shared<NiSourceTexture>(r, h); }},
            {"NiAlphaProperty", [](Reader& r, NiHeader& h) { return std::make_shared<NiAlphaProperty>(r, h); }},
            {"NiSpecularProperty", [](Reader& r, NiHeader& h) { return std::make_shared<NiSpecularProperty>(r, h); }},
            {"NiStencilProperty", [](Reader& r, NiHeader& h) { return std::make_shared<NiStencilProperty>(r, h); }},
            {"NiTextureTransformController", [](Reader& r, NiHeader& h) { return std::make_shared<NiTextureTransformController>(r, h); }},
            {"NiFloatInterpolator", [](Reader& r, NiHeader& h) { return std::make_shared<NiFloatInterpolator>(r, h); }},
            {"NiFloatData", [](Reader& r, NiHeader& h) { return std::make_shared<NiFloatData>(r, h); }},
            {"NiMorphWeightsController", [](Reader& r, NiHeader& h) { return std::make_shared<NiMorphWeightsController>(r, h); }},
            {"NiBillboardNode", [](Reader& r, NiHeader& h) { return std::make_shared<NiBillboardNode>(r, h); }},
            {"NiBooleanExtraData", [](Reader& r, NiHeader& h) { return std::make_shared<NiBooleanExtraData>(r, h); }},
            {"NiIntegerExtraData", [](Reader& r, NiHeader& h) { return std::make_shared<NiIntegerExtraData>(r, h); }},
            {"NiIntegersExtraData", [](Reader& r, NiHeader& h) { return std::make_shared<NiIntegersExtraData>(r, h); }},
            {"NiTriShape", [](Reader& r, NiHeader& h) { return std::make_shared<NiTriShape>(r, h); }},
            {"NiTriShapeData", [](Reader& r, NiHeader& h) { return std::make_shared<NiTriShapeData>(r, h); }},
            {"NiPixelData", [](Reader& r, NiHeader& h) { return std::make_shared<NiPixelData>(r, h); }},
            {"NiBoolData", [](Reader& r, NiHeader& h) { return std::make_shared<NiBoolData>(r, h); }},
};

void NiFile::parseBlocks() {
    blocks.reserve(header.numBlocks);  // Pre-allocate to avoid reallocations
    for (uint32_t i = 0; i < header.numBlocks; ++i) {
        std::string_view blockType = getReadableText(header.blockTypes[header.blockTypeIndex[i]]);

        printf("Current index: %u, blockType: %.*s\n", i, static_cast<int>(blockType.length()), blockType.data());

        auto it = factories.find(blockType);
        if (it != factories.end()) {
            blocks.push_back(it->second(reader, header));
        }
        else {
            printf("Unknown block type: %.*s\n", static_cast<int>(blockType.length()), blockType.data());
            uint32_t blockSize = header.blockSize[i];
            reader.read(blockSize);
        }
    }
}

void NiFile::parseDataStreams() {
    for (const auto& block : blocks) {
        if (!block) {
            printf("Null block encountered!\n");
            continue;
        }

        auto* niMesh = dynamic_cast<NiMesh*>(block.get());
        if (!niMesh) continue;

        for (const auto& dataStreamRef : niMesh->dataStreams) {
            auto dataStream = dataStreamRef.stream.getReference(*this);
            if (dataStream == nullptr) continue;

            for (const auto& semantic : dataStreamRef.componentSemantics) {
                Reader r(dataStream->data);
                std::string_view semanticName = semantic.name;

                if (semanticName == "POSITION") {
                    while (r.tell() + sizeof(Vector3) <= dataStream->numBytes) {
                        addStreamValue<DataStreamPosition>(dataStream->semanticData, r.read<Vector3>());
                    }
                }
                else if (semanticName == "NORMAL") {
                    while (r.tell() + sizeof(Vector3) <= dataStream->numBytes) {
                        addStreamValue<DataStreamNormal>(dataStream->semanticData, r.read<Vector3>());
                    }
                }
                else if (semanticName == "TEXCOORD") {
                    while (r.tell() + sizeof(TexCoord) <= dataStream->numBytes) {
                        addStreamValue<DataStreamTexCoord>(dataStream->semanticData, r.read<TexCoord>());
                    }
                }
                else if (semanticName == "COLOR") {
                    while (r.tell() + sizeof(Color4) <= dataStream->numBytes) {
                        addStreamValue<DataStreamColor>(dataStream->semanticData, r.read<Color4>());
                    }
                }
                else if (semanticName == "INDEX") {
                    while (r.tell() + sizeof(uint16_t) <= dataStream->numBytes) {
                        addStreamValue<DataStreamIndex>(dataStream->semanticData, r.read<uint16_t>());
                    }
                } // TOOD: implement rest
            }
        }
    }
}

NiFile::NiFile(const std::vector<uint8_t>& data) : reader(data), header(reader) {
	parseBlocks();
    parseDataStreams();
}

NiFile::NiFile(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open())
        throw std::runtime_error("Failed to open file: " + filePath);

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(size);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), size))
        throw std::runtime_error("Failed to read file: " + filePath);

	reader = Reader(buffer);
	header = NiHeader(reader);

    parseBlocks();
    parseDataStreams();
}