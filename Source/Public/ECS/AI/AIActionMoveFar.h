// Created by Przemys³aw Wiewióra 2024

#pragma once

#include "CoreMinimal.h"
#include "MyAIActionMove.h"

/**
 * Action used to move far from enemy unit (Ranged attack)
 */
class FAIActionMoveFar : public FMyAIActionMove
{
public:
	FAIActionMoveFar(FAITree* InAiTree);

	void SetTargetLocation(const FVector2D<int32>& InLocation) override;

protected:
	void MoveAwayFrom(const FVector2D<int32>& InLocation);

protected:
	float DistanceToMoveFrom;

};
