// Created by Przemys³aw Wiewióra 2024

#pragma once

#include "CoreMinimal.h"
#include "ECS/AI/AIActionMove.h"

class FUnitAIMemorySet;
/**
 * Action inherited from engine class
 */
class FAIActionAttack : public FAIActionBase
{
public:
	FAIActionAttack(FAITree* InAiTree);

	void Initialize() override;

	void StartAction() override;
	void EndAction() override;

	bool ShouldFinishAction() const override { return true; }

protected:
	std::shared_ptr<FUnitAIMemorySet> UnitAIMemorySetPtr;

};
