#pragma once
#include "../Blocks/NiNode.hpp"
#include "../Blocks/NiObject.hpp"
#include "../Reader.hpp"
#include "../Types/Ref.hpp"
#include "NiHeader.hpp"
#include <cstdint>
#include <memory>
#include <type_traits>
#include <vector>

struct NiFile
{
private:
    Reader reader;

public:
	NiHeader header;
	std::vector<std::shared_ptr<NiObject>> blocks;

	explicit NiFile(const std::vector<uint8_t>& data);
	NiFile(const NiFile&) = delete;
	NiFile& operator=(const NiFile&) = delete;
	NiFile& operator=(NiFile&&) = default;
	NiFile(NiFile&&) = default;

    template<typename T>
    std::vector<T*> getBlocksOfType() {
        static_assert(std::is_base_of_v<NiObject, T>, "T must derive from NiObject");

        std::vector<T*> result;

        for (const auto& obj : blocks) {
            if (auto* casted = dynamic_cast<T*>(obj.get())) {
                result.push_back(casted);
            }
        }

        return result;
    }

    std::vector<std::shared_ptr<NiNode>> getRootNodes() {
        std::vector<std::shared_ptr<NiNode>> roots;

        for (const auto& block : blocks) {
            if (auto node = dynamic_pointer_cast<NiNode>(block)) {
                roots.push_back(node);
            }
        }

        return roots;
    }

    
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