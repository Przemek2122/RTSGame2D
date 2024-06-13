#include "GamePCH.h"
#include "ECS/BulletProjectileEntity.h"

#include "Assets/AssetsManagerHelpers.h"
#include "Assets/Assets/TextureAsset.h"
#include "Assets/Collection/AssetCollectionItem.h"
#include "Assets/Collection/EngineAssetsCollection.h"
#include "ECS/Components/RenderComponent.h"

EBulletProjectileEntity::EBulletProjectileEntity(FEntityManager* InEntityManager)
	: EProjectileEntity(InEntityManager)
	, TextureAsset(nullptr)
{
}

void EBulletProjectileEntity::BeginPlay()
{
	Super::BeginPlay();

	EInitialProjectileParams InitialProjectileParams(120);

	SetProjectileParams(InitialProjectileParams);
}
