// Created by Przemys³aw Wiewióra 2024

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

	void MoveCloseTo(const FVector2D<int32> Location);

};
