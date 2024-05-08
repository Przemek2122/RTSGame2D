#include "GamePCH.h"
#include "ECS/InteractableEntityBase.h"

EInteractableEntityBase::EInteractableEntityBase(FEntityManager* InEntityManager)
	: EEntity(InEntityManager)
{
}

void EInteractableEntityBase::BeginPlay()
{
	EEntity::BeginPlay();

	RegisterToScreenSelection(GetEntityManagerOwner());
}

void EInteractableEntityBase::EndPlay()
{
	EEntity::EndPlay();


}
