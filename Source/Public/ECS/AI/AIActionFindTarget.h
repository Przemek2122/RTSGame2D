// Created by Przemys�aw Wiewi�ra 2024

#pragma once

#include "CoreMinimal.h"
#include "ECS/AI/AiActionBase.h"

struct FCollisionTile;
/**
 * Action used to find target for entity
 */
class FAIActionFindTarget : public FAIActionBase
{
public:
	explicit FAIActionFindTarget(FAITree* InAiTree);

	/** Begin FAIActionBase */
	void StartAction() override;
	bool ShouldFinishAction() const override;
	/** End FAIActionBase */

	void CheckCollision(const CArray<FCollisionTile*>& InCollisionTiles);

protected:
	EEntity* Entity;

};
