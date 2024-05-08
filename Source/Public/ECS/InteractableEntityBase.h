#pragma once

#include "Core/ECS/Entity.h"
#include "ECS/Interfaces/ScreenSelectionInterface.h"

class EInteractableEntityBase : public EEntity, public IScreenSelectionInterface
{
public:
	EInteractableEntityBase(FEntityManager* InEntityManager);

	void BeginPlay() override;
	void EndPlay() override;

};
