#include "GamePCH.h"
#include "ECS/Weapons/WeaponMele.h"

EWeaponMelee::EWeaponMelee(FEntityManager* InEntityManager)
	: EWeapon(InEntityManager)
{
}

void EWeaponMelee::BeginPlay()
{
	Super::BeginPlay();


}

void EWeaponMelee::PerformAttack()
{
	Super::PerformAttack();

	LOG_WARN("Melee attack");
}
