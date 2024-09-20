#include "GamePCH.h"
#include "ECS/Units/RangedUnitBase.h"

#include "ECS/AI/AIActionMove.h"

ERangedUnitBase::ERangedUnitBase(FEntityManager* InEntityManager)
	: EUnitBase(InEntityManager)
{
}

void ERangedUnitBase::BeginPlay()
{
	Super::BeginPlay();

	LOG_DEBUG("EMeleeUnitBase::BeginPlay");
}

void ERangedUnitBase::SetupAiActions()
{
	Super::SetupAiActions();

	FAITree* UnitAITree = CreateAiTree<FAITree>();
	FAiActionMove* AiActionMove = UnitAITree->CreateAction<FAiActionMove>();
}

const FRangedUnitSettings& ERangedUnitBase::GetRangedUnitSettings() const
{
	return RangedUnitSettings;
}
