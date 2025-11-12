#pragma once
#include "Blocks/NiNode.hpp"
#include "Blocks/NiObject.hpp"
#include "NiHeader.hpp"
#include "Reader.hpp"
#include "Types/Ref.hpp"
#include <cstdint>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>
#include <Defines.hpp>

struct NIFORGE_API NiFile
{
private:
    Reader reader;

public:
	NiHeader header;
	std::vector<std::shared_ptr<NiObject>> blocks;

	explicit NiFile(const std::vector<uint8_t>& data);
    explicit NiFile(const std::string& filePath);

	NiFile(const NiFile&) = delete;
	NiFile& operator=(const NiFile&) = delete;
	NiFile& operator=(NiFile&&) = default;
	NiFile(NiFile&&) = default;

    template<typename T>
    std::vector<T*> getBlocksOfType() const {
        static_assert(std::is_base_of_v<NiObject, T>, "T must derive from NiObject");

        std::vector<T*> result;
        result.reserve(blocks.size() / 4);  // Reserve some space (heuristic)

        for (const auto& obj : blocks) {
            if (auto* casted = dynamic_cast<T*>(obj.get())) {
                result.push_back(casted);
            }
        }

        return result;
    }

    std::vector<std::shared_ptr<NiNode>> getRootNodes() const {
        std::vector<std::shared_ptr<NiNode>> roots;
        roots.reserve(blocks.size() / 10);  // Reserve some space (heuristic)

        for (const auto& block : blocks) {
            if (auto node = dynamic_pointer_cast<NiNode>(block)) {
                roots.push_back(node);
            }
        }

        return roots;
    }

private:
    void parseBlocks();
    void parseDataStreams();
};

// NiFile is now fully defined
template <typename T>
T* Ref<T>::getReference(const NiFile& file) const {
    if (value == -1)
        return nullptr;

    if (value < 0 || static_cast<size_t>(value) >= file.blocks.size())
        return nullptr;

    return dynamic_cast<T*>(file.blocks[value].get());
}