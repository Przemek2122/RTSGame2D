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

	FAssetCollectionItem GetWeaponTexture() const override;

protected:
	void PerformAttack() override;

};
