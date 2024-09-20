#include "GamePCH.h"
#include "ECS/AI/AIActionFindTarget.h"

#include "ECS/Entity.h"
#include "ECS/Collision/BaseCollision.h"
#include "ECS/Collision/CollisionManager.h"
#include "ECS/Components/Collision/CollisionComponent.h"

FAIActionFindTarget::FAIActionFindTarget(FAITree* InAiTree)
	: FAIActionBase(InAiTree)
	, Entity(nullptr)
{
}

void FAIActionFindTarget::StartAction()
{
	Super::StartAction();

	Entity = GetEntity();
	UCollisionComponent* CollisionComponent = Entity->GetComponentByClass<UCollisionComponent>();
	if (CollisionComponent != nullptr)
	{
		CArray<FCollisionBase*> CollisionObjectsArray = CollisionComponent->GetCollisionObjectsArray();
		for (FCollisionBase* ObjectsArray : CollisionObjectsArray)
		{
			const CArray<FCollisionTile*>& Tiles = ObjectsArray->GetCurrentlyLocatedTiles();
			if (Tiles.Size() > 0)
			{
				CheckCollision(Tiles);
			}
		}
	}
	else
	{
		LOG_WARN("Missing collision component, AIActionFindTarget will not work.");
	}
}

bool FAIActionFindTarget::ShouldFinishAction() const
{
	// We do everything on single thread so it can be finished immediately
	return true;
}

void FAIActionFindTarget::CheckCollision(const CArray<FCollisionTile*>& InCollisionTiles)
{
	for (FCollisionTile* CollisionTile : InCollisionTiles)
	{
		for (FCollisionBase* CollisionObject : CollisionTile->CollisionObjects)
		{
			EEntity* CollisionObjectEntity = CollisionObject->GetCollisionComponent()->GetEntity();
			if (CollisionObjectEntity != Entity)
			{
				LOG_WARN("Found other entity in collision!");
			}
		}
	}
}
