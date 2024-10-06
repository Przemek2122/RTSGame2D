#include "GamePCH.h"
#include "ECS/Weapons/Weapon.h"

#include "Core/RTSAssetCollection.h"
#include "ECS/Components/RenderComponent.h"

EWeapon::EWeapon(FEntityManager* InEntityManager)
	: EWeaponBase(InEntityManager)
{
	TransformComponent = CreateComponent<UParentComponent>("TransformComponent");
	RenderComponent = TransformComponent->CreateComponent<URenderComponent>("RenderComponent");
}

void EWeapon::BeginPlay()
{
	Super::BeginPlay();

	SetWeaponTexture(GetWeaponTexture());
}

FAssetCollectionItem EWeapon::GetWeaponTexture() const
{
	return RTSAssetCollection::DefaultWeapon;
}

void EWeapon::SetWeaponTexture(const FAssetCollectionItem& InAssetCollectionItem)
{
	RenderComponent->SetImage(InAssetCollectionItem);
}
