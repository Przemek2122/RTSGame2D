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

	/** Begin EEntity */
	void SetupAIActions() override;
	/** End EEntity */

	const FMeleeUnitSettings& GetMeleeUnitSettings() const { return MeleeUnitSettings; }

	void OnRandomHostileSelected(EEntity* InRandomHostileEntity) override;

protected:
	FMeleeUnitSettings MeleeUnitSettings;
	FAITree* UnitAITree;

};
