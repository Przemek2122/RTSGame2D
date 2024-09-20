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

void ERangedUnitBase::SetupAiActions()
{
	Super::SetupAiActions();

	// Create simple unit AI
	FAITree* UnitAITree = CreateAiTree<FAITree>();
	UnitAITree->CreateAction<FAIActionMove>();
	UnitAITree->CreateAction<FAIActionFindTarget>();
}

const FRangedUnitSettings& ERangedUnitBase::GetRangedUnitSettings() const
{
	return RangedUnitSettings;
}
