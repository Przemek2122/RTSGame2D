#pragma once

#include "InteractableEntityBase.h"
#include "Core/RTSAssetCollection.h"

class UArrowComponent;
class UTargetingComponent;
class UMoveComponent;
class UHealthComponent;
class UBaseTransformComponent;
class URenderComponent;

class EUnitBase : public EInteractableEntityBase
{
public:
	EUnitBase(FEntityManager* InEntityManager);
	~EUnitBase() override = default;

	/** Begin EEntity */
	void BeginPlay() override;
	/** End EEntity */

	/** Begin IScreenSelectionInterface */
	FVector2D<int> GetLocation() override;
	FVector2D<int> GetSize() override;
	void OnSelect() override;
	void OnDeSelect() override;
	void OnDoAction(const FVector2D<int>& ActionLocation) override;
	/** End IScreenSelectionInterface */

	/** Override to choose unit asset */
	virtual const FAssetCollectionItem& GetUnitAsset();

protected:
	UBaseTransformComponent* TransformComponent;
	URenderComponent* RenderComponent;
	UHealthComponent* HealthComponent;
	UMoveComponent* MoveComponent;
	UTargetingComponent* TargetingComponent;

};
