#pragma once

#include "ECS/UnitBase.h"

/** Ranged unit properties */
struct FRangedUnitSettings
{
	FRangedUnitSettings()
		: AttackDistanceMin(0)
		, AttackDistanceMax(0)
		, Damage(0)
	{
	}

	float AttackDistanceMin;
	float AttackDistanceMax;
	float Damage;
};

/**
 * Base unit for ranged units
 */
class ERangedUnitBase : public EUnitBase
{
public:
	ERangedUnitBase(FEntityManager* InEntityManager);

	/** Begin EEntity */
	void BeginPlay() override;
	void SetupAiActions() override;
	/** End EEntity */

	const FRangedUnitSettings& GetRangedUnitSettings() const;

protected:
	FRangedUnitSettings RangedUnitSettings;

};
