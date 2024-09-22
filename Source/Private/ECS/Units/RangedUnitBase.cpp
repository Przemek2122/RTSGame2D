#include "GamePCH.h"
#include "ECS/Units/RangedUnitBase.h"

#include "ECS/AI/AIActionFindTarget.h"
#include "ECS/AI/AIActionMove.h"

ERangedUnitBase::ERangedUnitBase(FEntityManager* InEntityManager)
	: EUnitBase(InEntityManager)
	, UnitAITree(nullptr)
{
}

void ERangedUnitBase::BeginPlay()
{
	Super::BeginPlay();

	LOG_DEBUG("ERangedUnitBase::BeginPlay");
}

void ERangedUnitBase::SetupAiActions()
{
	Super::SetupAiActions();

	// Create simple unit AI
	UnitAITree = CreateAiTree<FAITree>();
	UnitAITree->CreateAction<FAIActionMove>();
	FAIActionFindTarget* AIActionFindTarget = UnitAITree->CreateAction<FAIActionFindTarget>();
	AIActionFindTarget->OnHostileEntitiesFound.BindObject(this, &ERangedUnitBase::OnHostilesFound);
}

const FRangedUnitSettings& ERangedUnitBase::GetRangedUnitSettings() const
{
	return RangedUnitSettings;
}

void ERangedUnitBase::OnHostilesFound(const CArray<EEntity*> InHostileEntities)
{
	if (!InHostileEntities.IsEmpty())
	{
		EEntity* RandomEntity = InHostileEntities.GetRandomValue();
		if (RandomEntity != nullptr)
		{
			UParentComponent* RootComponentOfEntity = dynamic_cast<UParentComponent*>(RandomEntity->GetRootComponent());
			if (RootComponentOfEntity != nullptr)
			{
				FAIActionMove* AIActionMove = UnitAITree->GetActionByClass<FAIActionMove>();
				if (AIActionMove != nullptr)
				{
					const FVector2D<int>& EntityLocation = RootComponentOfEntity->GetLocation();

					AIActionMove->TryStartAction();
					AIActionMove->SetTargetLocation(EntityLocation);
				}
			}
		}
	}
}
