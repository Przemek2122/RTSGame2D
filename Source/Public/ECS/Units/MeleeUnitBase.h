#pragma once

#include "ECS/UnitBase.h"

/** Melee unit properties */
struct FMeleeUnitSettings
{
	FMeleeUnitSettings()
		: AttackDistanceMax(0)
		, Damage(0)
	{
	}

	float AttackDistanceMax;
	float Damage;
};

/**
 * Base unit for melee unit
 */
class EMeleeUnitBase : public EUnitBase
{
public:
	EMeleeUnitBase(FEntityManager* InEntityManager);

	const FMeleeUnitSettings& GetMeleeUnitSettings() const;

protected:
	FMeleeUnitSettings MeleeUnitSettings;

};
