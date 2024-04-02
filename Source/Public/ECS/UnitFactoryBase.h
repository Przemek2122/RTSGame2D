#pragma once

#include "Core/RTSAssetCollection.h"
#include "Core/ECS/Entity.h"
#include "ECS/Interfaces/ScreenSelectionInterface.h"

class UBaseTransformComponent;
class URenderComponent;

class EUnitFactoryBase : public EEntity, public IScreenSelectionInterface
{
public:
	EUnitFactoryBase(FEntityManager* InEntityManager);
	~EUnitFactoryBase() override = default;

	/** Begin EEntity */
	void BeginPlay() override;
	/** End EEntity */

	/** Begin IScreenSelectionInterface */
	FVector2D<int> GetLocation() override;
	FVector2D<int> GetSize() override;
	void OnSelect() override;
	void OnDeSelect() override;
	/** End IScreenSelectionInterface */

	virtual std::string GetFactoryDisplayName();
	virtual FRTSAsset GetFactoryAsset();

protected:
	UBaseTransformComponent* TransformComponent;
	URenderComponent* RenderComponent;

};
