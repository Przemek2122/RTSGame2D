// Created by Przemys³aw Wiewióra 2024

#pragma once

#include "CoreMinimal.h"
#include "MyAIActionMove.h"

/**
 * Action used to move close to enemy unit (Melee attack)
 */
class FAIActionMoveClose : public FMyAIActionMove
{
public:
	FAIActionMoveClose(FAITree* InAiTree);
	~FAIActionMoveClose() override;

	void Initialize() override;

	void SetTargetLocation(const FVector2D<int>& InLocation) override;

	void OnMovementStopped();

protected:
	void MoveCloseTo(const FVector2D<int32>& InLocation);

protected:
	/** When is it close enough for unit to stop? */
	float StopDistance;
	float PreviousStopDistance;

};
