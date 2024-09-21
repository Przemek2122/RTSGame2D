// Created by Przemys³aw Wiewióra 2024

#pragma once

#include "CoreMinimal.h"
#include "ECS/AI/AiActionBase.h"

class UCollisionComponent;
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
	void Initialize() override;
	void StartAction() override;
	bool ShouldFinishAction() const override;
	bool IsActionReady() const override;
	/** End FAIActionBase */

protected:
	void SetUnlockActionTimer();

	void IterateCollisionToFindHostiles();
	void CheckCollisionTiles(const CArray<FCollisionTile*>& InCollisionTiles);
	void OnCollisionIterationFinished();

	void OnActionDelayFinished(FOptionalTimerParams* OptionalTimerParams);

protected:
	/** Owning entity */
	EEntity* Entity;

	/** Owning entity collision component */
	UCollisionComponent* CollisionComponent;

	/** bool used to limit number of detections of hostiles */
	bool bIsActionReady;

	/** Time to run this action every x time */
	float ActionLockTime;

	/** Array with found hostiles */
	CArray<EEntity*> HostileEntitiesFound;

	std::shared_ptr<FTimer> ActionStartDelayTimer;

};
