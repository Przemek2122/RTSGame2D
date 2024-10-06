#include "GamePCH.h"
#include "ECS/Weapons/WeaponRanged.h"

#include "Core/RTSAssetCollection.h"

EWeaponRanged::EWeaponRanged(FEntityManager* InEntityManager)
	: EWeapon(InEntityManager)
{
}

FAssetCollectionItem EWeaponRanged::GetWeaponTexture() const
{
	return RTSAssetCollection::SpearWeapon;
}

void EWeaponRanged::PerformAttack()
{
	Super::PerformAttack();


}
