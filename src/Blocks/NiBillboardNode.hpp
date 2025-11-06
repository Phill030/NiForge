#pragma once
#include "Core/NiHeader.hpp"
#include "Reader.hpp"
#include "NiNode.hpp"
#include <cstdint>

enum class NIFORGE_API BillboardMode : uint16_t
{
    ALWAYS_FACE_CAMERA = 0,  // Align billboard and camera forward vector. Minimized rotation.
    ROTATE_ABOUT_UP = 1,  // Align billboard and camera forward vector while allowing rotation around the up axis.
    RIGID_FACE_CAMERA = 2,  // Align billboard and camera forward vector. Non-minimized rotation.
    ALWAYS_FACE_CENTER = 3,  // Billboard forward vector always faces camera center. Minimized rotation.
    RIGID_FACE_CENTER = 4,  // Billboard forward vector always faces camera center. Non-minimized rotation.
    BSROTATE_ABOUT_UP = 5,  // Billboard rotates only around its local Z axis (stays in local X-Y plane).
    ROTATE_ABOUT_UP2 = 9   // Billboard rotates only around up axis (same as ROTATE_ABOUT_UP?).
};

// Determines the way the billboard will react to the camera.
// Billboard mode is stored in lowest 3 bits although Oblivion vanilla nifs uses values higher than 7.
struct NIFORGE_API NiBillboardNode : NiNode
{
public:
    BillboardMode billboardMode;
    NiBillboardNode(Reader& reader, const NiHeader& header) : NiNode(reader, header) {
		billboardMode = static_cast<BillboardMode>(reader.read<uint16_t>());
    }
};