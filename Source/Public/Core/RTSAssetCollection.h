#pragma once

#include "Assets/Collection/BaseAssetsCollection.h"

/**
 * Place for all assets used in the game for reuse
 */
class RTSAssetCollection : public FBaseAssetsCollection
{
public:
	inline static const FAssetCollectionItem FactoryBase = { "FactoryBase", R"(Assets\Textures\Factories\FactoryBase.png)" };
	inline static const FAssetCollectionItem UnitBase = { "Unit", R"(Assets\Textures\Units\UnitBase.png)" };

	// Add more assets here
	// ...
};