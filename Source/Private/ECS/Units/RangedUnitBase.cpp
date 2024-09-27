#include "GamePCH.h"
#include "ECS/Units/RangedUnitBase.h"

#include "ECS/AI/AIActionFindTarget.h"
#include "ECS/AI/AIActionMoveFar.h"

ERangedUnitBase::ERangedUnitBase(FEntityManager* InEntityManager)
	: EUnitBase(InEntityManager)
{
}

void ERangedUnitBase::BeginPlay()
{
	Super::BeginPlay();

	LOG_DEBUG("ERangedUnitBase::BeginPlay");
}

void ERangedUnitBase::SetupAIActions()
{
	Super::SetupAIActions();

	if (Movement_AITree != nullptr)
	{
		Movement_AITree->CreateAction<FAIActionMoveFar>();
	}
}

void ERangedUnitBase::OnRandomHostileSelected(EEntity* InRandomHostileEntity)
{
	Super::OnRandomHostileSelected(InRandomHostileEntity);

	FAIActionMove* AIActionMove = Movement_AITree->GetActionByClass<FAIActionMove>();
	if (AIActionMove != nullptr && !AIActionMove->IsActionRunning())
	{
		const FVector2D<int>& EntityLocation = InRandomHostileEntity->GetLocation();

		const bool bIsMoveActionStarting = AIActionMove->TryStartAction();
		if (bIsMoveActionStarting)
		{
			AIActionMove->SetTargetLocation(EntityLocation);
		}
		else
		{
			LOG_WARN("Unable to start move action");
		}
	}
}
