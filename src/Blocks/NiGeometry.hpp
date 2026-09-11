#pragma once
#include "NiAvObject.hpp"
#include "NiSkinInstance.hpp"
#include "Data/NiGeometryData.hpp"
#include "Types/Ref.hpp"
#include "Types/MaterialData.hpp"

struct NIFORGE_API NiGeometry : NiAvObject
{
public:
	Ref<NiGeometryData> data;
	Ref<NiSkinInstance> skinInstance;
	MaterialData materialData;
	NiGeometry(Reader& reader, const NiHeader& header) : NiAvObject(reader, header),
		data(Ref<NiGeometryData>(reader)),
		skinInstance(Ref<NiSkinInstance>(reader)) {
		materialData = MaterialData(reader, header);
	}
};