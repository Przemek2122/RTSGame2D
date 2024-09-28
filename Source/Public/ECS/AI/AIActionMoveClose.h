// Created by Przemys�aw Wiewi�ra 2024

#pragma once

#include "CoreMinimal.h"
#include "ECS/AI/AIActionMove.h"

/**
 * Action used to move close to enemy unit (Melee attack)
 */
class FAIActionMoveClose : public FAIActionMove
{
public:
	explicit FAIActionMoveClose(FAITree* InAiTree);

	void SetTargetLocation(const FVector2D<int>& InLocation) override;

protected:
	void MoveCloseTo(const FVector2D<int32>& InLocation);

protected:
	/** When is it close enough for unit to stop? */
	float StopDistance;

};