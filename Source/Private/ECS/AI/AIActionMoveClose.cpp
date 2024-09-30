#include "GamePCH.h"
#include "ECS/AI/AIActionMoveClose.h"

#include "ECS/Components/MoveComponent.h"

FAIActionMoveClose::FAIActionMoveClose(FAITree* InAiTree)
	: FAIActionMove(InAiTree)
	, StopDistance(40.f)
	, PreviousStopDistance(-1.f)
{
}

FAIActionMoveClose::~FAIActionMoveClose()
{
	if (CurrentMoveComponent != nullptr)
	{
		CurrentMoveComponent->OnStoppedMovement.UnBindObject(this, &FAIActionMoveClose::OnMovementStopped);

		OnMovementStopped();
	}
}

void FAIActionMoveClose::Initialize()
{
	Super::Initialize();

	if (CurrentMoveComponent != nullptr)
	{
		CurrentMoveComponent->OnStoppedMovement.BindObject(this, &FAIActionMoveClose::OnMovementStopped);
	}
}

void FAIActionMoveClose::SetTargetLocation(const FVector2D<int>& InLocation)
{
	MoveCloseTo(InLocation);
}

void FAIActionMoveClose::OnMovementStopped()
{
	CurrentMoveComponent->SetStoppingDistance(PreviousStopDistance);
}

void FAIActionMoveClose::MoveCloseTo(const FVector2D<int32>& InLocation)
{
	if (CurrentMoveComponent != nullptr && !CurrentMoveComponent->IsMoving())
	{
		const FVector2D<int32> CurrentLocation = CurrentMoveComponent->GetLocation();
		const int32 Distance = InLocation.DistanceTo(CurrentLocation);

		if (Distance > StopDistance)
		{
			PreviousStopDistance = CurrentMoveComponent->GetStoppingDistance();
			CurrentMoveComponent->SetStoppingDistance(StopDistance);
			CurrentMoveComponent->SetTargetMoveLocation(InLocation);
		}
	}
}
