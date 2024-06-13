#pragma once

#include "CoreMinimal.h"
#include "ECS/Entities/ProjectileEntity.h"

class EBulletProjectileEntity : public EProjectileEntity
{
public:
	EBulletProjectileEntity(FEntityManager* InEntityManager);

	void BeginPlay() override;

protected:
	FTextureAsset* TextureAsset;

};
