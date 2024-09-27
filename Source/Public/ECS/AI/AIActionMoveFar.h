// Created by Przemys³aw Wiewióra 2024

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

	void MoveAwayFrom(const FVector2D<int32> Location);

};
