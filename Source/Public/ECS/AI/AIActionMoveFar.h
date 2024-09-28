// Created by Przemys�aw Wiewi�ra 2024

#pragma once

#include "CoreMinimal.h"
#include "ECS/AI/AIActionMove.h"

/**
 * Action used to move far from enemy unit (Ranged attack)
 */
class FAIActionMoveFar : public FAIActionMove
{
public:
	explicit FAIActionMoveFar(FAITree* InAiTree);

	void SetTargetLocation(const FVector2D<int32>& InLocation) override;

protected:
	void MoveAwayFrom(const FVector2D<int32>& InLocation);

protected:
	float DistanceToMoveFrom;

};