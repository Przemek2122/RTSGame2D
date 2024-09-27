#include "GamePCH.h"
#include "ECS/AI/AIActionMoveFar.h"

#include "ECS/Components/MoveComponent.h"

FAIActionMoveFar::FAIActionMoveFar(FAITree* InAiTree)
	: FAIActionMove(InAiTree)
	, DistanceToMoveFrom(120)
{
}

void FAIActionMoveFar::SetTargetLocation(const FVector2D<int32>& InLocation)
{
	MoveAwayFrom(InLocation);
}

void FAIActionMoveFar::MoveAwayFrom(const FVector2D<int32>& InLocation)
{
	if (CurrentMoveComponent != nullptr)
	{
		EEntity* Entity = GetOwnerEntity();
		FVector2D<int32> ToLocation = Entity->GetLocation();
		const int32 CurrentDistance = InLocation.DistanceTo(ToLocation);

		if (CurrentDistance < DistanceToMoveFrom)
		{
			const float DistanceToMoveLeft = DistanceToMoveFrom - CurrentDistance;

			const FVector2D<int32> EscapingPoint = FVector2D<int32>::FindEscapingPoint(InLocation, ToLocation, DistanceToMoveLeft);

			CurrentMoveComponent->SetTargetMoveLocation(EscapingPoint);
		}
	}
}
