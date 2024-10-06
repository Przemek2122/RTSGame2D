#include "GamePCH.h"
#include "ECS/Weapons/WeaponRanged.h"

EWeaponRanged::EWeaponRanged(FEntityManager* InEntityManager)
	: EWeapon(InEntityManager)
{
}

void EWeaponRanged::PerformAttack()
{
	Super::PerformAttack();


}
