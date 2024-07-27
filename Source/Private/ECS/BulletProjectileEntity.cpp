#include "GamePCH.h"
#include "ECS/BulletProjectileEntity.h"

#include "Assets/Assets/TextureAsset.h"
#include "Core/RTSAssetCollection.h"
#include "ECS/Components/RenderComponent.h"

EBulletProjectileEntity::EBulletProjectileEntity(FEntityManager* InEntityManager)
	: EProjectileEntity(InEntityManager)
	, TextureAsset(nullptr)
{
}

void EBulletProjectileEntity::BeginPlay()
{
	Super::BeginPlay();

	EProjectileMovementParams ProjectileMovementParams(120);
	SetProjectileMovementParams(ProjectileMovementParams);

	GetRenderComponent()->SetImage(RTSAssetCollection::BulletBase);
}
