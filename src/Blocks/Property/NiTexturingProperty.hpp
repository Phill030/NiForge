#pragma once
#include "Core/NiHeader.hpp"
#include "Reader.hpp"
#include "Types/Matrix.hpp"
#include "Types/ShaderTexDesc.hpp"
#include "Types/TexDesc.hpp"
#include "NiProperty.hpp"
#include <cstdint>
#include <optional>
#include <vector>

// Describes how a fragment shader should be configured for a given piece of geometry. 
struct NiTexturingProperty : NiProperty
{
public:
	uint16_t flags;
	uint32_t numTextures;
	bool hasBaseTexture;
	std::optional<TexDesc> baseTexture;

	bool hasDarkTexture;
	std::optional<TexDesc> darkTexture;

	bool hasDetailTexture;
	std::optional<TexDesc> detailTexture;

	bool hasGlossTexture;
	std::optional<TexDesc> glossTexture;

	bool hasGlowTexture;
	std::optional<TexDesc> glowTexture;

	bool hasBumpMapTexture;
	std::optional<TexDesc> bumpMapTexture;
	std::optional<float> bumpMapLumaScale;
	std::optional<float> bumpMapLumaOffset;
	std::optional<Matrix<2,2>> bumpMapMatrix;

	bool hasNormalTexture;
	std::optional<TexDesc> normalTexture;

	bool hasParallaxTexture;
	std::optional<TexDesc> parallaxTexture;

	bool hasDecal0Texture;
	std::optional<TexDesc> decal0Texture;

	uint32_t numShaderTextures;
	std::vector<ShaderTexDesc> shaderTextures;

	NiTexturingProperty(Reader& reader, const NiHeader& header): NiProperty(reader, header) {
		flags = reader.read<uint16_t>();
		numTextures = reader.read<uint32_t>();

		hasBaseTexture = reader.read<bool>();
		if(hasBaseTexture)
			baseTexture = TexDesc(reader, header);


		hasDarkTexture = reader.read<bool>();
		if(hasDarkTexture)
			darkTexture = TexDesc(reader, header);

		hasDetailTexture = reader.read<bool>();
		if (hasDetailTexture)
			detailTexture = TexDesc(reader, header);

		hasGlossTexture = reader.read<bool>();
		if (hasGlossTexture)
			glossTexture = TexDesc(reader, header);

		hasGlowTexture = reader.read<bool>();
		if (hasGlowTexture)
			glowTexture = TexDesc(reader, header);

		hasBumpMapTexture = reader.read<bool>();
		if (hasBumpMapTexture) {
			bumpMapTexture = TexDesc(reader, header);
			bumpMapLumaScale = reader.read<float>();
			bumpMapLumaOffset = reader.read<float>();
			bumpMapMatrix = reader.readMatrix<2,2>();
		}


		hasNormalTexture = reader.read<bool>();
		if (hasNormalTexture)
			normalTexture = TexDesc(reader, header);

		hasParallaxTexture = reader.read<bool>();
		if (hasParallaxTexture)
			parallaxTexture = TexDesc(reader, header);

		hasDecal0Texture = reader.read<bool>();
		if (hasDecal0Texture)
			decal0Texture = TexDesc(reader, header);

		numShaderTextures = reader.read<uint32_t>();
		shaderTextures.reserve(numShaderTextures);
		for (uint32_t i = 0; i < numShaderTextures; i++) {
			shaderTextures.push_back(ShaderTexDesc(reader, header));
		}
	}
};