#pragma once

#include "Weapon.h"

/**
 * Base class for ranged weapon
 * (shooting some kind of projectiles)
 */
class EWeaponRanged : public EWeapon
{
public:
	EWeaponRanged(FEntityManager* InEntityManager);

	FAssetCollectionItem GetWeaponTexture() const override;

protected:
	void PerformAttack() override;

};
