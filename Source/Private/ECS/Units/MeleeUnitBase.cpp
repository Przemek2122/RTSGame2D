#include "GamePCH.h"
#include "ECS/Units/MeleeUnitBase.h"

EMeleeUnitBase::EMeleeUnitBase(FEntityManager* InEntityManager): EUnitBase(InEntityManager)
{
}

void EMeleeUnitBase::BeginPlay()
{
	Super::BeginPlay();

	LOG_WARN("Correct class created");
}

const FMeleeUnitSettings& EMeleeUnitBase::GetMeleeUnitSettings() const
{
	return MeleeUnitSettings;
}
