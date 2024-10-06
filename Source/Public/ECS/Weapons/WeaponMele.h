#pragma once

#include "Weapon.h"

class UCollisionComponent;
class USquareCollisionComponent;
/**
 * Base class for melee weapons
 * (Any weapon which has direct attack)
 */
class EWeaponMelee : public EWeapon
{
public:
	EWeaponMelee(FEntityManager* InEntityManager);

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

	FAssetCollectionItem GetWeaponTexture() const override;

protected:
	void PerformAttack() override;

	void OnAttackDelayFinished() override;

	void OnMeleeAttack(UCollisionComponent* InCollisionComponent);

private:
	/** Component for making damage */
	USquareCollisionComponent* AttackSquareCollision;

	/** Per hit damage */
	float Damage;

	bool bIsAttacking;

	size_t WeaponPushTime;
	size_t WeaponReturnTime;

	size_t AttackStartTime;

	/** Cached default location of spear */
	FTransform2DLocation StartingRelativeLocationOfSpear;

	/** How much should spear move when attacking? */
	FTransform2DLocation AttackRelativeSpearOffset;

};
