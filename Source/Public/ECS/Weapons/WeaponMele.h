#pragma once

#include "Weapon.h"

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

private:
	bool bIsAttacking;

	size_t WeaponPushTime;
	size_t WeaponReturnTime;

	size_t AttackStartTime;

	/** Cached default location of spear */
	FTransformLocation StartingRelativeLocationOfSpear;

	/** How much should spear move when attacking? */
	FTransformLocation AttackRelativeSpearOffset;

};
