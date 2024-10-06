#pragma once

#include "InteractableEntityBase.h"
#include "Core/RTSAssetCollection.h"
#include "Weapons/Weapon.h"

class FUnitAIMemorySet;
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
	FVector2D<int32> GetLocation() override;
	FVector2D<int32> GetSize() override;
	void OnSelect() override;
	void OnDeSelect() override;
	void OnDoAction(const FVector2D<int>& ActionLocation) override;
	/** End IScreenSelectionInterface */

	/** Override to choose unit asset */
	virtual const FAssetCollectionItem& GetUnitAsset();

	EWeapon* GetWeapon() const { return Weapon; }

	virtual void OnRandomHostileSelected(EEntity* InRandomHostileEntity);

protected:
	UParentComponent* TransformComponent;
	URenderComponent* RenderComponent;
	UHealthComponent* HealthComponent;
	UMoveComponent* MoveComponent;
	UCollisionComponent* CollisionComponent;

	/** Unit AIMemoryTree */
	std::shared_ptr<FUnitAIMemorySet> UnitAIMemorySetPtr;

	/** AI Tree for finding hostiles */
	FAITree* FindHostile_AITree;

	/** AI Tree for unit movement */
	FAITree* Movement_AITree;

	/** AI Tree for attack */
	FAITree* Attack_AITree;

	/** Class for weapon entity */
	FEntityClassStorage<EWeapon> WeaponClass;

	/** Weapon instance */
	EWeapon* Weapon;

};
