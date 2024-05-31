#pragma once

#include "InteractableEntityBase.h"
#include "Core/RTSAssetCollection.h"

class USquareCollisionComponent;
class URenderComponent;

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
	virtual FAssetCollectionItem GetFactoryAsset();

protected:
	UParentComponent* TransformComponent;
	URenderComponent* RenderComponent;
	USquareCollisionComponent* SquareCollisionComponent;

};
