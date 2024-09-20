#include "GamePCH.h"
#include "ECS/InteractableEntityBase.h"

#include "Core/GameModes/RTSGameMode.h"
#include "ECS/Components/TeamComponent.h"

EInteractableEntityBase::EInteractableEntityBase(FEntityManager* InEntityManager)
	: EEntity(InEntityManager)
{
	TeamComponent = CreateComponent<UTeamComponent>("TeamComponent");
}

bool EInteractableEntityBase::CanSelect()
{
	bool bCanSelect = false;

	if (TeamComponent != nullptr)
	{
		FUserId OwnerUserId = TeamComponent->GetOwnerUserId();

		FRTSGameMode* RTSGameMode = dynamic_cast<FRTSGameMode*>(GetGameMode());
		if (RTSGameMode != nullptr)
		{
			FUserId LocalUserId = RTSGameMode->GetLocalController()->GetUserId();

			bCanSelect = (LocalUserId == OwnerUserId);
		}
	}

	return bCanSelect;
}

void EInteractableEntityBase::BeginPlay()
{
	Super::BeginPlay();

	RegisterToScreenSelection(GetEntityManagerOwner());
}

void EInteractableEntityBase::EndPlay()
{
	Super::EndPlay();

	UnregisterFromScreenSelection();
}

UTeamComponent* EInteractableEntityBase::GetTeamComponent() const
{
	return TeamComponent;
}
