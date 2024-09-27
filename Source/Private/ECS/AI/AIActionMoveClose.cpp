#include "GamePCH.h"
#include "ECS/AI/AIActionMoveClose.h"

#include "ECS/Components/MoveComponent.h"

FAIActionMoveClose::FAIActionMoveClose(FAITree* InAiTree)
	: FAIActionMove(InAiTree)
	, StopDistance(40.f)
{
}

void FAIActionMoveClose::SetTargetLocation(const FVector2D<int>& InLocation)
{
	MoveCloseTo(InLocation);
}

void FAIActionMoveClose::MoveCloseTo(const FVector2D<int32>& InLocation)
{
	if (CurrentMoveComponent != nullptr)
	{
		CurrentMoveComponent->SetStoppingDistance(StopDistance);
		CurrentMoveComponent->SetTargetMoveLocation(InLocation);
	}
}
