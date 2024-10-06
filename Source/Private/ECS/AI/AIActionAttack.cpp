#include "GamePCH.h"
#include "ECS/AI/AIActionAttack.h"

#include "ECS/UnitBase.h"
#include "ECS/AI/UnitAIMemorySet.h"

FAIActionAttack::FAIActionAttack(FAITree* InAiTree)
	: FAIActionBase(InAiTree)
{
}

void FAIActionAttack::Initialize()
{
	Super::Initialize();

	UnitAIMemorySetPtr = GetOwnerEntity()->GetAIMemorySetByClass<FUnitAIMemorySet>();
	if (UnitAIMemorySetPtr == nullptr)
	{
		LOG_WARN("Missing FUnitAIMemorySet, AI will not work.");
	}
}

void FAIActionAttack::StartAction()
{
	Super::StartAction();

	if (UnitAIMemorySetPtr != nullptr)
	{
		EWeapon* UnitWeapon = UnitAIMemorySetPtr->ThisUnit->GetWeapon();
		if (UnitWeapon != nullptr && UnitAIMemorySetPtr->CurrentTarget != nullptr && UnitWeapon->CanAttack())
		{
			UnitWeapon->Attack();
		}
	}
}

void FAIActionAttack::EndAction()
{
	Super::EndAction();
}
