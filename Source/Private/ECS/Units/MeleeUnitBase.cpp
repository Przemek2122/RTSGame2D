#include "GamePCH.h"
#include "ECS/Units/MeleeUnitBase.h"

EMeleeUnitBase::EMeleeUnitBase(FEntityManager* InEntityManager): EUnitBase(InEntityManager)
{
}

const FMeleeUnitSettings& EMeleeUnitBase::GetMeleeUnitSettings() const
{
	return MeleeUnitSettings;
}
