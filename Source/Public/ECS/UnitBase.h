#pragma once

#include "InteractableEntityBase.h"
#include "Core/RTSAssetCollection.h"

class UCollisionComponent;
class UArrowComponent;
class UTargetingComponent;
class UMoveComponent;
class UHealthComponent;
class UParentComponent;
class URenderComponent;

/**
 * Base unit for any unit type
 * Contains:
 * - Collision,
 * - Movement
 * - Health
 * - Render
 * @TODO And more
 */
class EUnitBase : public EInteractableEntityBase
{
public:
	EUnitBase(FEntityManager* InEntityManager);
	~EUnitBase() override = default;

	/** Begin EEntity */
	void BeginPlay() override;
	void SetupAIActions() override;
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

	void OnHostilesFound(const CArray<EEntity*> InHostileEntities);

	virtual void OnRandomHostileSelected(EEntity* InRandomHostileEntity);

protected:
	UParentComponent* TransformComponent;
	URenderComponent* RenderComponent;
	UHealthComponent* HealthComponent;
	UMoveComponent* MoveComponent;
	UTargetingComponent* TargetingComponent;
	UCollisionComponent* CollisionComponent;

	FAITree* FindHostile_AITree;
	FAITree* Movement_AITree;

};
