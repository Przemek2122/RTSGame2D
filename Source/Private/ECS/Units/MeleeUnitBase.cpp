#include "GamePCH.h"
#include "ECS/Units/MeleeUnitBase.h"

#include "ECS/AI/AIActionFindTarget.h"
#include "ECS/AI/AIActionMove.h"

EMeleeUnitBase::EMeleeUnitBase(FEntityManager* InEntityManager)
	: EUnitBase(InEntityManager)
{
}

void EMeleeUnitBase::BeginPlay()
{
	Super::BeginPlay();

	LOG_DEBUG("EMeleeUnitBase::BeginPlay");
}

void EMeleeUnitBase::SetupAiActions()
{
	Super::SetupAiActions();

	// Create simple unit AI
	FAITree* UnitAITree = CreateAiTree<FAITree>();
	UnitAITree->CreateAction<FAIActionMove>();
	UnitAITree->CreateAction<FAIActionFindTarget>();
}

const FMeleeUnitSettings& EMeleeUnitBase::GetMeleeUnitSettings() const
{
	return MeleeUnitSettings;
}
