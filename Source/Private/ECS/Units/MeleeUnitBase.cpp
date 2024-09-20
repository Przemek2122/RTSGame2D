#include "GamePCH.h"
#include "ECS/Units/MeleeUnitBase.h"

EMeleeUnitBase::EMeleeUnitBase(FEntityManager* InEntityManager)
	: EUnitBase(InEntityManager)
{
}

void EMeleeUnitBase::BeginPlay()
{
	Super::BeginPlay();

	LOG_DEBUG("EMeleeUnitBase::BeginPlay");
}

void EMeleeUnitBase::SetupAiActions()
{
	Super::SetupAiActions();


}

const FMeleeUnitSettings& EMeleeUnitBase::GetMeleeUnitSettings() const
{
	return MeleeUnitSettings;
}
