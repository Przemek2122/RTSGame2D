#include "GamePCH.h"
#include "ECS/Units/RangedUnitBase.h"

ERangedUnitBase::ERangedUnitBase(FEntityManager* InEntityManager): EUnitBase(InEntityManager)
{
}

const FRangedUnitSettings& ERangedUnitBase::GetRangedUnitSettings() const
{
	return RangedUnitSettings;
}
