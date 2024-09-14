#pragma once

#include "InteractableEntityBase.h"
#include "Core/RTSAssetCollection.h"

class USquareCollisionComponent;
class URenderComponent;

struct FConstructionUnitData
{
	FConstructionUnitData() = default;
	FConstructionUnitData(const std::string& InName, FAssetCollectionItem InAssetCollectionItem);

	/** Name of the unit */
	std::string Name;

	/** Image to display */
	FAssetCollectionItem AssetCollectionItem;

};

class EUnitFactoryBase : public EInteractableEntityBase
{
public:
	EUnitFactoryBase(FEntityManager* InEntityManager);
	~EUnitFactoryBase() override = default;

	/** Begin EEntity */
	void BeginPlay() override;
	/** End EEntity */

	/** Begin IScreenSelectionInterface */
	FVector2D<int> GetLocation() override;
	FVector2D<int> GetSize() override;
	void OnSelect() override;
	void OnDeSelect() override;
	/** End IScreenSelectionInterface */

	/** Override to choose factory asset */
	virtual const FAssetCollectionItem& GetFactoryAsset() const;

	/** Override to choose factory name */
	virtual std::string GetFactoryName() const;

	virtual CArray<FConstructionUnitData> GetUnits() const;

	/** Adds one unit to build queue */
	void AddUnitToQueue();

	/** Removes unit from build queue (if present) */
	void RemoveUnitFromQueue();

protected:
	/** Root transform component */
	UParentComponent* TransformComponent;

	/** Render component for factory */
	URenderComponent* RenderComponent;

	/** Square collision for Factory */
	USquareCollisionComponent* SquareCollisionComponent;

};
