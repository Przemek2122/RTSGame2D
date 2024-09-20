// Created by Przemys³aw Wiewióra 2024

#pragma once

#include "CoreMinimal.h"
#include "ECS/AI/AiActionBase.h"

/**
 * Action used to find target for entity
 */
class FAIActionFindTarget : public FAIActionBase
{
public:
	explicit FAIActionFindTarget(FAITree* InAiTree);


};
