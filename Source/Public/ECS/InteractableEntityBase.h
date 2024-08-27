#pragma once

#include "Core/ECS/Entity.h"
#include "ECS/Interfaces/ScreenSelectionInterface.h"

class UTeamComponent;

class EInteractableEntityBase : public EEntity, public IScreenSelectionInterface
{
public:
	EInteractableEntityBase(FEntityManager* InEntityManager);

	bool CanSelect() override;

	void BeginPlay() override;
	void EndPlay() override;

	UTeamComponent* GetTeamComponent() const;

private:
	UTeamComponent* TeamComponent;

};
