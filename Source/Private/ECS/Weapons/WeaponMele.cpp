#include "GamePCH.h"
#include "ECS/Weapons/WeaponMele.h"

#include "Core/RTSAssetCollection.h"

EWeaponMelee::EWeaponMelee(FEntityManager* InEntityManager)
	: EWeapon(InEntityManager)
{
}

void EWeaponMelee::BeginPlay()
{
	Super::BeginPlay();


}

FAssetCollectionItem EWeaponMelee::GetWeaponTexture() const
{
	return RTSAssetCollection::SpearWeapon;
}

void EWeaponMelee::PerformAttack()
{
	Super::PerformAttack();


}
