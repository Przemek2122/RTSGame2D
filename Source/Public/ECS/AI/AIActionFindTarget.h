// Created by Przemys³aw Wiewióra 2024

#pragma once

#include "CoreMinimal.h"
#include "ECS/AI/AiActionBase.h"

struct FOptionalTimerParams;
struct FCollisionTile;
/**
 * Action used to find target for entity
 */
class FAIActionFindTarget : public FAIActionBase
{
public:
	explicit FAIActionFindTarget(FAITree* InAiTree);

	/** Begin FAIActionBase */
	void StartAction() override;
	bool ShouldFinishAction() const override;
	bool IsActionReady() const override;
	/** End FAIActionBase */

	void CheckCollision(const CArray<FCollisionTile*>& InCollisionTiles);

protected:
	void LockActionForPeriodOfTime();

	void OnActionDelayFinished(FOptionalTimerParams* OptionalTimerParams);

protected:
	EEntity* Entity;
	bool bIsActionReady;
	float ActionLockTime;
	std::shared_ptr<FTimer> ActionStartDelayTimer;

};
