#include "GamePCH.h"
#include "ECS/AI/MyAIActionMove.h"

#include "ECS/AI/UnitAIMemorySet.h"

FMyAIActionMove::FMyAIActionMove(FAITree* InAiTree)
	: FAIActionMove(InAiTree)
{
}

void FMyAIActionMove::Initialize()
{
	Super::Initialize();

	UnitAIMemorySetPtr = GetOwnerEntity()->GetAIMemorySetByClass<FUnitAIMemorySet>();
	if (UnitAIMemorySetPtr == nullptr)
	{
		LOG_WARN("Missing FUnitAIMemorySet, AI will not work.");
	}
}
