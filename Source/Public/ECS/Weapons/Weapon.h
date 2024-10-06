#pragma once

#include "ECS/Entities/WeaponBase.h"

struct FAssetCollectionItem;
class URenderComponent;

class EWeapon : public EWeaponBase
{
public:
	EWeapon(FEntityManager* InEntityManager);

	void BeginPlay() override;

	/** Get weapon render component */
	URenderComponent* GetRenderComponent() const { return RenderComponent; }

	virtual FAssetCollectionItem GetWeaponTexture() const;
	virtual void SetWeaponTexture(const FAssetCollectionItem& InAssetCollectionItem);

private:
	/** Root component */
	UParentComponent* TransformComponent;

	/** Weapon render component */
	URenderComponent* RenderComponent;

};
