#pragma once

#include "Core\ECS\Entity.h"
#include "ECS/Interfaces/ScreenSelectionInterface.h"

class UTransformComponent;
class URenderComponent;

class EUnitBase : public EEntity, public IScreenSelectionInterface
{
public:
	EUnitBase(FEntityManager* InEntityManager);
	~EUnitBase() override = default;

	/** Begin IScreenSelectionInterface */
	FVector2D<int> GetLocation() override;
	FVector2D<int> GetSize() override;
	/** End IScreenSelectionInterface */

protected:
	UTransformComponent* TransformComponent;
	URenderComponent* RenderComponent;

};
