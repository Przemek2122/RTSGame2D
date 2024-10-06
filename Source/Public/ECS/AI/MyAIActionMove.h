// Created by Przemys³aw Wiewióra 2024

#pragma once

#include "CoreMinimal.h"
#include "ECS/AI/AIActionMove.h"

class FUnitAIMemorySet;
/**
 * Action inherited from engine class
 */
class FMyAIActionMove : public FAIActionMove
{
public:
	FMyAIActionMove(FAITree* InAiTree);

	void Initialize() override;

protected:
	std::shared_ptr<FUnitAIMemorySet> UnitAIMemorySetPtr;

};
