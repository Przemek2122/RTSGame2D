#include "GamePCH.h"
#include "ECS/Units/RangedUnitBase.h"

#include "ECS/AI/AIActionFindTarget.h"
#include "ECS/AI/AIActionMove.h"

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


}

const FRangedUnitSettings& ERangedUnitBase::GetRangedUnitSettings() const
{
	return RangedUnitSettings;
}

void ERangedUnitBase::OnRandomHostileSelected(EEntity* InRandomHostileEntity)
{
	Super::OnRandomHostileSelected(InRandomHostileEntity);

	UParentComponent* RootComponentOfEntity = dynamic_cast<UParentComponent*>(InRandomHostileEntity->GetRootComponent());
	if (RootComponentOfEntity != nullptr)
	{
		FAIActionMove* AIActionMove = Movement_AITree->GetActionByClass<FAIActionMove>();
		if (AIActionMove != nullptr)
		{
			const FVector2D<int>& EntityLocation = RootComponentOfEntity->GetLocation();

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
}
