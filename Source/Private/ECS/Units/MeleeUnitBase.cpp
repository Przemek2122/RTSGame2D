#include "GamePCH.h"
#include "ECS/Units/MeleeUnitBase.h"

#include "ECS/AI/AIActionFindTarget.h"
#include "ECS/AI/AIActionMoveClose.h"
#include "ECS/Weapons/WeaponMele.h"

EMeleeUnitBase::EMeleeUnitBase(FEntityManager* InEntityManager)
	: EUnitBase(InEntityManager)
	, UnitAITree(nullptr)
{
	WeaponClass.Set<EWeaponMelee>();
}

void EMeleeUnitBase::SetupAIActions()
{
	Super::SetupAIActions();

	if (Movement_AITree != nullptr)
	{
		Movement_AITree->CreateAction<FAIActionMoveClose>();
	}
}

void EMeleeUnitBase::OnRandomHostileSelected(EEntity* InRandomHostileEntity)
{
	Super::OnRandomHostileSelected(InRandomHostileEntity);

	FAIActionMove* AIActionMove = Movement_AITree->GetActionByClass<FAIActionMove>();
	if (AIActionMove != nullptr && !AIActionMove->IsActionRunning())
	{
		const FVector2D<int32>& EntityLocation = InRandomHostileEntity->GetLocation();

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
