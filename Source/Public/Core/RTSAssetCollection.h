#pragma once

/**
 * Base class for all assets - Will keep AssetName and AssetPath.
 */
struct FRTSAsset
{
protected:
	std::string AssetName;
	std::string AssetPath;

public:
	FRTSAsset(std::string InAssetName, std::string InAssetPath)
		: AssetName(std::move(InAssetName))
		, AssetPath(std::move(InAssetPath))
	{
	}

	const std::string& GetAssetName() const { return AssetName; }
	const std::string& GetAssetPath() const { return AssetPath; }

};

/**
 * Place for all assets used in the game for reuse
 */
class RTSAssetCollection
{
public:
	inline static FRTSAsset FactoryBase = { "FactoryBase", R"(Assets\Textures\Factories\FactoryBase.png)" };
	inline static FRTSAsset UnitBase = { "Unit", R"(Assets\Textures\Units\UnitBase.png)" };

	// Add more assets here
	// ...
};
